/* Handle #pragma, system V.4 style.  Supports #pragma weak and #pragma pack.
   Copyright (C) 1992, 1997, 1998, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include "config.h"
#include "system.h"
#include "rtl.h"
#include "tree.h"
#include "except.h"
#include "function.h"
#include "defaults.h"
#include "c-pragma.h"
#include "flags.h"
#include "toplev.h"

#ifdef HANDLE_GENERIC_PRAGMAS

#ifdef HANDLE_PRAGMA_PACK
/* When structure field packing is in effect, this variable is the
   number of bits to use as the maximum alignment.  When packing is not
   in effect, this is zero.  */

extern int maximum_field_alignment;
#endif


#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
typedef struct align_stack
{
  int                  alignment;
  tree                 id;
  struct align_stack * prev;
} align_stack;

static struct align_stack * alignment_stack = NULL;

static int  push_alignment PROTO((int, tree));
static int  pop_alignment  PROTO((int, tree));

/* Push an alignment value onto the stack.  */
static int
push_alignment (alignment, id)
     int alignment;
     tree id;
{
  align_stack * entry;

  entry = (align_stack *) xmalloc (sizeof (* entry));

  if (entry == NULL)
    {
      warning ("Out of memory pushing #pragma pack");
      return 0;
    }

  entry->alignment  = maximum_field_alignment;
  entry->id         = id;
  entry->prev       = alignment_stack;

  alignment_stack = entry;

  maximum_field_alignment = alignment;

  return 1;
}

/* Undo a push of an alignment onto the stack.  If the alignment argument
   is > 0, then make that the new alignment after popping the stack instead 
   of using TOS. See the combination rules in the #pragma pack(pop[,id][,n]) 
   syntax for details.  */
static int
pop_alignment (alignment, id)
     int alignment;
     tree id;
{
  align_stack * entry;

  /* If popping an empty stack, revert to default packing. Defer warning
     if we got an identifier.  */
  if (alignment_stack == NULL && id == NULL)
    {
      warning 
        ("#pragma pack(pop) encountered without matching #pragma pack(push)");
      maximum_field_alignment = 0;
      return 1;
    }

  /* If we got an identifier, strip away everything above the target
     entry so that the next step will restore the state that existed
     just before the identifier was pushed on the stack.  */
  if (id)
    {
      align_stack * popped = NULL;
      for (entry = alignment_stack; entry; 
           popped = entry, entry = entry->prev)
	{
	  if (popped)
	    free (popped);

	  if (entry->id == id)
	    {
	      alignment_stack = entry;
	      break;
	    }
	}
      if (entry == NULL)
        {
	  warning
	    ("#pragma pack(pop,%s) encountered without matching #pragma pack(push,%s)",
	     IDENTIFIER_POINTER (id), IDENTIFIER_POINTER (id));
	  alignment_stack = NULL;
	  maximum_field_alignment = 0;
	  return 1;
	}
    }

  entry = alignment_stack->prev;

  /* The new alignment is either a user specified one (combination rule)
     or restored from the stack. */
  maximum_field_alignment = 
    (alignment > 0) ? alignment : alignment_stack->alignment;

  free (alignment_stack);
  alignment_stack = entry;

  return 1;
}
#endif /* HANDLE_PRAGMA_PACK_PUSH_POP */

/* Handle one token of a pragma directive.  TOKEN is the current token, and
   STRING is its printable form.  Some front ends do not support generating
   tokens, and will only pass in a STRING.  Also some front ends will reuse
   the buffer containing STRING, so it must be copied to a local buffer if
   it needs to be preserved.

   If STRING is non-NULL, then the return value will be ignored, and there
   will be futher calls to handle_pragma_token() in order to handle the rest of
   the line containing the #pragma directive.  If STRING is NULL, the entire
   line has now been presented to handle_pragma_token() and the return value
   should be zero if the pragma flawed in some way, or if the pragma was not
   recognised, and non-zero if it was successfully handled.

   If HANDLE_PRAGMA_WEAK is defined, handle the weak directives using
   the following syntax:

   #pragma weak name [= alias]

   If HANDLE_PRAGMA_PACK is defined, handle the pack directives using 
   the following syntax:
                                       
   #pragma pack([n])
   
   Specifies packing alignment for structure and union members. The 
   packing alignment is set at the data-declaration level by the pack 
   pragma. The pragma takes effect at the first structure or union 
   declaration after the pragma is seen; the pragma has no effect on 
   definitions.
   
   When you use #pragma pack(n), where n is 1, 2, 4, 8, or 16, each
   structure member after the first is stored on the smaller member type
   or n-byte boundaries. If you use #pragma pack without an argument,
   the alignment reverts to the default for the target.
   
   If HANDLE_PRAGMA_PACK_PUSH_POP is defined, also handle the 
   following syntax:
   
   #pragma pack({ push | pop} [,identifier] [,n])
   
   Each occurrence of a #pragma pack with a push argument stores the
   current packing alignment on a stack; If you provide a value for n, 
   that value becomes the new packing value. If you specify an 
   identifier, the identifier is associated with the new packing value.
   
   Each occurrence of a #pragma pack with a pop argument pops the stack
   and uses the value the new packing alignment. If you use pop and the 
   internal compiler stack is empty, the new alignment is set to be
   the default alignment for target, and an warning is issued.  If you 
   use pop and specify a value for n, that value becomes the new packing 
   value. If you use pop and specify an identifier, all values stored on 
   the stack are removed from the stack until a matching identifier is 
   found. The packing value associated with the identifier is also 
   removed from the stack and the packing value that existed just before 
   the identifier was pushed becomes the new packing value. If no 
   matching identifier is found, the packing value set to the default
   and a warning is issued.  */

int
handle_pragma_token (string, token)
     const char * string;
     tree token;
{
  static enum pragma_state state = ps_start;
  static enum pragma_state type;
  static char * name;
  static char * value;
  static int align = -1;
  static tree id;

  /* If we have reached the end of the #pragma directive then
     determine what value we should return.  */
  
  if (string == NULL)
    {
      int ret_val = 0;

      switch (type)
	{
	default:
	  abort ();
	  break;

	case ps_done:
	  /* The pragma was not recognised.  */
	  break;
	  
#ifdef HANDLE_PRAGMA_PACK	  
	case ps_pack:
	  if (state == ps_right)
	    {
	      maximum_field_alignment = align;
	      ret_val = 1;
	    }
	  else
	    {
	      ret_val = 1; /* Ignore the pragma.  */
	      warning ("malformed `#pragma pack'");
	    }
	  break;
#endif /* HANDLE_PRAGMA_PACK */
	  
#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
	case ps_push:
	  if (state == ps_right)
	    ret_val = push_alignment (align, id);
	  else
	    {
	      ret_val = 1; /* Ignore the pragma.  */
	      warning ("malformed '#pragma pack(push[,id][,n])'");
	    }
	  break;
	  
	case ps_pop:
	  if (state == ps_right)
	    ret_val = pop_alignment (align, id);
	  else
	    {
	      ret_val = 1; /* Ignore the pragma.  */
	      warning ("malformed '#pragma pack(pop[,id][,n])'");
	    }
	  break;
#endif /* HANDLE_PRAGMA_PACK_PUSH_POP */
	  
#ifdef HANDLE_PRAGMA_WEAK
	case ps_weak:
	  if (HANDLE_PRAGMA_WEAK)
	    {
	      if (state == ps_name)
		ret_val = add_weak (name, NULL);
	      else if (state == ps_value)
		ret_val = add_weak (name, value);
	      else
		warning ("malformed `#pragma weak'");
	    }
	  else
	    ret_val = 1; /* Ignore the pragma.  */
	  break;
#endif /* HANDLE_PRAGMA_WEAK */
	}

      type = state = ps_start;
      id = NULL_TREE;
      align = -1;
      
      return ret_val;
    }

  /* If we have been given a token, but it is not an identifier,
     or a small constant, then something has gone wrong.  */
  if (token)
    {
      switch (TREE_CODE (token))
	{
	case IDENTIFIER_NODE:
	  break;
	  
	case INTEGER_CST:
	  if (TREE_INT_CST_HIGH (token) != 0)
	    return 0;
	  break;
	  
	default:
	  return 0;
	}
    }
      
  switch (state)
    {
    case ps_start:
      type = state = ps_done;
#ifdef HANDLE_PRAGMA_PACK
      if (strcmp (string, "pack") == 0)
	type = state = ps_pack;
#endif
#ifdef HANDLE_PRAGMA_WEAK
      if (strcmp (string, "weak") == 0)
	type = state = ps_weak;
#endif	  
      break;
      
#ifdef HANDLE_PRAGMA_WEAK
    case ps_weak:
      name = permalloc (strlen (string) + 1);
      if (name == NULL)
	{
	  warning ("Out of memory parsing #pragma weak");
	  state = ps_bad;
	}
      else
	{
	  strcpy (name, string);
	  state = ps_name;
	}
      break;
      
    case ps_name:
      state = (strcmp (string, "=") ? ps_bad : ps_equals);
      break;

    case ps_equals:
      value = permalloc (strlen (string) + 1);
      if (value == NULL)
	{
	  warning ("Out of memory parsing #pragma weak");
	  state = ps_bad;
	}
      else
	{
	  strcpy (value, string);
	  state = ps_value;
	}
      break;

    case ps_value:
      state = ps_bad;
      break;
#endif /* HANDLE_PRAGMA_WEAK */
      
#ifdef HANDLE_PRAGMA_PACK
    case ps_pack:
      state = (strcmp (string, "(") ? ps_bad : ps_left);
      break;

    case ps_left:

      if (token == NULL_TREE)
	{
	  /* #pragma pack () resets packing rules to their
	     defaults.  */
	  if (strcmp (string, ")") == 0)
	    {
	      align = 0;
	      state = ps_right;
	    }
	  else
	    state = ps_bad;
	}
      else if (TREE_CODE (token) == INTEGER_CST)
	goto handle_align;

#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
      else if (TREE_CODE (token) == IDENTIFIER_NODE)
	{
	  if (strcmp (string, "push") == 0)
	    type = state = ps_push;
	  else if (strcmp (string, "pop") == 0)
	    type = state = ps_pop;
	  else
	    state = ps_bad;
	}
#endif
      else
	state = ps_bad;
      break;

    handle_align:
      /* User specified alignment in bytes, but is converted to bits 
         before use.  */
      align = TREE_INT_CST_LOW (token);
      switch (align)
	{
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	  align *= 8;
	  state = ps_align;
	  break;

	default:
#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
          warning 
	    ("Alignment must be a small power of two, not %d, in #pragma %s",
	     align, (type == ps_pop) ? "pop" : "pack");
#else
          warning 
	    ("Alignment must be a small power of two, not %d, in #pragma pack",
	     align);
#endif
	  state = ps_bad;
	  break;
	}
      break;

    case ps_align:
      state = (strcmp (string, ")") ? ps_bad : ps_right);
      break;

    case ps_right:
      state = ps_bad;
      break;
#endif /* HANDLE_PRAGMA_PACK */

#ifdef HANDLE_PRAGMA_PACK_PUSH_POP
    case ps_push:
      /* If no alignment is specified, push the current alignment.  */
      align = maximum_field_alignment;

      /* fall through. */
    case ps_pop:
      /* If no alignment is specified, we'll just use the stored one.  */
      if (strcmp (string, ",") == 0)
        state = ps_comma;
      else if (strcmp (string, ")") == 0)
        {
	  state = ps_right;
	}
      else
	state = ps_bad;
      break;

    case ps_comma:
      /* Id or <n> or both specified. */
      if (token && TREE_CODE (token) == IDENTIFIER_NODE)
	{
	  id = token;
	  state = ps_id;
	  break;
	}

      /* else no id, but <n> specified, so fall through */
    case ps_comma2:
      if (token && TREE_CODE (token) == INTEGER_CST)
	goto handle_align;
      else
	state = ps_bad;
      break;

    case ps_id:
      if (strcmp (string, ",") == 0)
        state = ps_comma2;
      else if (strcmp (string, ")") == 0)
	state = ps_right;
      else
	state = ps_bad;
      break;

#endif /* HANDLE_PRAGMA_PACK_PUSH_POP */
      
    case ps_bad:
    case ps_done:
      break;

    default:
      abort ();
    }

  return 1;
}
#endif /* HANDLE_GENERIC_PRAGMAS */
