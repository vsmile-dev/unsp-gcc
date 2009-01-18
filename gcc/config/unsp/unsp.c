#include <stdio.h>
#include "config.h"
#include "system.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "insn-flags.h"
#include "output.h"
#include "insn-attr.h"
#include "tree.h"
#include "flags.h"
#include "except.h"
#include "function.h"
#include "recog.h"
#include "expr.h"
#include "toplev.h"

struct func_list
{
  struct func_list *next;
  char *name;
};

struct var_sec_list
{
  struct var_sec_list *next;
  char *var_name;
  char *sec_name;
};

struct unsp_frame_info current_frame_info;
struct unsp_frame_info zero_frame_info;

static struct func_list *extern_head;
static struct func_list *exports_head;
static struct func_list *far_ptr_head;
static struct func_list *used_far_ptr_head;

static struct var_sec_list *var_sec_head;

enum machine_mode unsp_compare_mode;
rtx unsp_compare_op0;
rtx unsp_compare_op1;

char unsp_tmpstr[512];

const char *unsp_packed_string_prefix_string;
char unsp_packed_string_prefix;

unsigned int unsp_isa = 0x0101;
const char *unsp_isa_string;

void
override_options ()
{
  if (unsp_isa_string != NULL)
    {
      if (strcmp (unsp_isa_string, "1.0") == 0)
        unsp_isa = 0x0100;
      else if (strcmp (unsp_isa_string, "1.1") == 0)
        unsp_isa = 0x0101;
      else if (strcmp (unsp_isa_string, "1.2") == 0)
        unsp_isa = 0x0102;
      else if (strcmp (unsp_isa_string, "1.3") == 0)
        unsp_isa = 0x0103;
      else if (strcmp (unsp_isa_string, "2.0") == 0)
        unsp_isa = 0x0200;
      else
        {
          warning ("Unknown ISA specified, default to ISA=1.1");
          unsp_isa = 0x0101;
        }
    }

  if (unsp_packed_string_prefix_string)
    {
      if (strcmp (unsp_packed_string_prefix_string, "NULL") == 0)
	{
	  unsp_packed_string_prefix = 0;
	}
      else if (strlen (unsp_packed_string_prefix_string) != 1)
        {
	  error ("Only one prefix character is allowed");
	  error ("Default prefix character `@' used");
	  unsp_packed_string_prefix = '@';
	}
      else
        {
	  unsp_packed_string_prefix = *unsp_packed_string_prefix_string;

	  if ((unsp_packed_string_prefix >= 'A')
	      && (unsp_packed_string_prefix <= 'Z'))
	    {
	    }
	  else if ((unsp_packed_string_prefix >= 'a')
	           && (unsp_packed_string_prefix <= 'z'))
	    {
	    }
	  else if ((unsp_packed_string_prefix >= '0')
	           && (unsp_packed_string_prefix <= '9'))
	    {
	    }
	  else if (unsp_packed_string_prefix == '@')
	    {
	    }
	  else if (unsp_packed_string_prefix == '_')
	    {
	    }
	  else if (unsp_packed_string_prefix == '$')
	    {
	    }
	  else
	    {
	      error ("Only one of A-Za-z0-9@_$ or NULL is allowed");
	      error ("Default prefix character `@' used");
	      unsp_packed_string_prefix = '@';
	    }
        }
    }
  else
    unsp_packed_string_prefix = '@';
}

int
set_bit_immediate_operand (rtx op)
{
  int i, val;

  if (GET_CODE (op) != CONST_INT)
    return 0;

  val = INTVAL (op);
  for (i = 1; i <= 16; i++)
    {
      if (val == (1 << (i - 1)))
        return i;
    }

  return 0;
}

int
clear_bit_immediate_operand (rtx op)
{
  int i, val;

  if (GET_CODE (op) != CONST_INT)
    return 0;

  val = INTVAL (op) & 0xFFFF;
  for (i = 1; i <= 16; i++)
    {
      if (val == (0xFFFF ^ (1 << (i - 1))))
        return i;
    }

  return 0;
}

/*
int
symbolic_address_p (op)
     rtx op;
{
  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
    case LABEL_REF:
      return 1;

    case CONST:
      op = XEXP (op, 0);
      return ((GET_CODE (XEXP (op, 0)) == SYMBOL_REF ||
	       GET_CODE (XEXP (op, 0)) == LABEL_REF)
	      && GET_CODE (XEXP (op, 1)) == CONST_INT);
    default:
      return 0;
    }
}

int
part_memory_operand (op)
     rtx op;
{
  if (GET_CODE (op) == MEM)
  {
    switch (GET_CODE (XEXP (op, 0)))
    {
      case CONST:
      case SYMBOL_REF:
      case LABEL_REF:
      case CONST_INT:
	return 1;
    }
  }
  return 0;
}
*/

int
nonregister_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  if (general_operand (op, mode) && GET_CODE (op) != REG)
    return 1;

  return 0;
}

int
direct16_memory_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  if (general_operand (op, mode) && GET_CODE (op) == MEM)
    {
      switch (GET_CODE (XEXP (op, 0)))
        {
        case CONST:
        case SYMBOL_REF:
        case LABEL_REF:
        case CONST_INT:
	  return 1;
/*
	case REG:
	  if (REGNO (XEXP (op, 0)) >= FIRST_PSEUDO_REGISTER)
	    return 1;
*/
        }
    }
  return 0;
}

int
non_direct16_memory_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  if (general_operand (op, mode)
      && GET_CODE (op) == MEM
      && direct16_memory_operand (op, mode) == 0)
        return 1;
  return 0;
}

/* operands which is a register or direct16 memory that can be
   the left hand side of ALU_OP.  */
int
lvalue_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  if (general_operand (op, mode)
      && (direct16_memory_operand (op, mode) || REG_P (op)))
    return 1;
  return 0;
}

int
call_address_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
    case LABEL_REF:
      return 1;

    case CONST:
      op = XEXP (op, 0);
      return ((GET_CODE (XEXP (op, 0)) == SYMBOL_REF
               || GET_CODE (XEXP (op, 0)) == LABEL_REF)
	      && GET_CODE (XEXP (op, 1)) == CONST_INT);
    default:
      return 0;
    }
}

int
initial_elimination_offset (from, to)
     int from;
     int to;
{
  int offset;

  if (from == FRAME_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
    offset = 0;
  else if (from == ARG_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM) {
      int regno;

      offset = 0;
      for (regno = 0; regno < 5; regno++)
	if (regs_ever_live[regno] && ! call_used_regs[regno])
	  offset++;
      offset += get_frame_size() + 3;
    }
  else if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    offset = 1;
  else if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    {
      int regno;

      offset = 0;
      for (regno = 0; regno < 5; regno++)
	if (regs_ever_live[regno] && ! call_used_regs[regno])
	  offset++;
      offset += get_frame_size() + 3 + 1;
    }
  else
    {
      fprintf (stderr, "Invalid elimination offset calculation\n");
      fprintf (stderr, "FROM=%d, TO=%d\n\n\n", from, to);
      abort ();
    }

  if (TARGET_DEBUG_UNSP_GCC)
    {
      fprintf (stderr, "FROM=%d, TO=%d, OFFSET=%d\n", from, to, offset);
    }
  return offset;
}

int
unsp_makes_calls ()
{
  rtx insn;
  for (insn = get_insns (); insn; insn = next_insn (insn))
    if (GET_CODE (insn) == CALL_INSN)
      return (1);
  return 0;
}

int
compute_frame_size (size)
     int size;
{
  int total_size;
  int var_size = size;
  int reg_size = 0;
  int regno;

  for (regno = 0; regno < 5; regno++)
    if (regs_ever_live[regno] && ! call_used_regs[regno])
      reg_size++;

  total_size = var_size + reg_size;
  /* Save other computed information.  */
  current_frame_info.total_size  = total_size;
  current_frame_info.var_size    = var_size;
  current_frame_info.reg_size    = reg_size;
  current_frame_info.initialized = reload_completed;
  current_frame_info.function_makes_calls = unsp_makes_calls ();

  return total_size;
}

/* Generate the assembly code for function entry.
   FILE is an stdio stream to output the code to.
   SIZE is an int: how many units of temporary storage to allocate.  */
void
function_prologue (file, size)
     FILE *file;
     int  size;
{
  int total_size;
  if (/*DECL_LANG_FLAG_0 (current_function_decl) ||
      TREE_LANG_FLAG_0 (current_function_decl)*/
      UNSP_ISR_FLAG (current_function_decl) )
    {
      fprintf (file, "\t// ISR ATTRIBUTE FUNCTION, PUSH r1,bp\n");
      fprintf(file, "\tpush r1,bp to [sp]\n\n");
    }
  //else
    {
    /* Reset the frame info */
      current_frame_info = zero_frame_info;

      compute_frame_size (size);
      total_size = current_frame_info.total_size;
      fprintf (file, "\t// total=%d, vars=%d\n",
               current_frame_info.total_size, current_frame_info.var_size);

      fprintf (file, "\t// frame_pointer_needed: %d\n", frame_pointer_needed);

      /* Save frame_pointer */
      if (frame_pointer_needed)
        {
	  if (!UNSP_ISR_FLAG (current_function_decl))
	    fprintf(file, "\tpush bp to [sp]\n");
          if (total_size)
	    fprintf (file, "\tsp-=%d\n", total_size);
          fprintf (file, "\tbp=sp+1\n\n");
        }
      else
        fprintf (file, "\t// Don't need to save frame_pointer\n\n");
    }
}

void
function_epilogue (file, size)
     FILE *file;
     int   size;
{
  int offset_sp = current_frame_info.total_size;
  fprintf (file, "\n" );
  if (frame_pointer_needed)
    {
      if (offset_sp)
	fprintf (file, "\tsp+=%d\n", offset_sp);
      if (!UNSP_ISR_FLAG (current_function_decl))
	fprintf (file, "\tpop bp from [sp]\n");
    }
  if (UNSP_ISR_FLAG (current_function_decl))
    {
      fprintf (file, "\t// ISR ATTRIBUTE FUNCTION, POP r1,bp\n");
      fprintf(file, "\tpop r1,bp from [sp]\n");
      fprintf (file, "\treti\n");
    }
  else
      fprintf (file, "\tretf\n");
}

void
notice_update_cc (exp)
     rtx exp;
{
  if (GET_CODE (exp) == SET)
    {
      /* Jumps do not alter the cc's.  */
      if (SET_DEST (exp) == pc_rtx)
	return;
      else if (GET_CODE (SET_DEST (exp)) == MEM)
	return;
      /* Function calls clobber the cc's.  */
      else if (GET_CODE (SET_SRC (exp)) == CALL)
	{
	  CC_STATUS_INIT;
	  return;
	}
      /* Tests and compares set the cc's in predictable ways.  */
      else if (SET_DEST (exp) == cc0_rtx)
	{
	  CC_STATUS_INIT;
	  cc_status.value1 = SET_SRC (exp);
	  return;
	}
      else
	{
	  CC_STATUS_INIT;
	  return;
	}
     }
   else
    {
      CC_STATUS_INIT;
    }
}

/* Compute the cost of computing a constant rtl expression X
   whose rtx-code is CODE. */
int
unsp_rtx_cost(x, code, outer_code)
     rtx x;
     enum rtx_code code;
     enum rtx_code outer_code;
{
  enum machine_mode mode = GET_MODE (x);

  if (TARGET_DEBUG_UNSP_GCC)
    {
      fprintf (stderr, "UNSP_RTX_COST.......\n");
      debug_rtx (x);
    }

  switch (code)
    {
    case ASHIFT:
    case ROTATE:
    case ASHIFTRT:
    case LSHIFTRT:
    case ROTATERT:
      if (mode == QImode && GET_CODE (XEXP (x, 1)) == CONST_INT)
	{
	  int i;

	  i = INTVAL (XEXP (x, 1)) % BITS_PER_WORD;
	  if (i < 0)
	    i += BITS_PER_WORD;

          /* Number of shift operation needed:
	     1.. 4 => 1    5.. 8 => 2    9..12 => 3    13..15 => 4 */
	  i = i / 4 + 1;
	  return i;
	}
      else
	return 1000; /* shift by a function call */
    case MULT:
      if (mode == QImode)
	return 2;
      else
	return 1000;
    case PLUS:
    case AND:
    case IOR:
    case XOR:
    case MINUS:
    case COMPARE:
      {
	rtx op0 = XEXP (x, 0);
	rtx op1 = XEXP (x, 1);
	enum rtx_code code0 = GET_CODE (op0);
	enum rtx_code code1 = GET_CODE (op1);
	int times;

	if (GET_MODE (XEXP (x, 0)) == QImode)
	  times = 1;
	else if (GET_MODE (XEXP (x, 0)) == HImode)
	  times = 3;
	else
	  return 1000;

	if (code0 == REG)
	  {
	    if (code1 == CONST_INT)
	      {
	      	if (INTVAL (op1) >= 0 && INTVAL (op1) < 64)
	          return 1*times;
	        return 2*times;
	      }
	    else if (code1 == REG)
	      {
	      	return 2*times;
	      }
	    else
	      {
	      	return 2*times;
	      }
	  }
	else if (code1 == MEM)
	  {
            return 3*times;
	  }
	else if (code0 == SUBREG)
	  {
            return 3*times;
	  }
      }
    case NEG:
      {
	rtx op0 = XEXP (x, 0);
	enum rtx_code code0 = GET_CODE (op0);
	int times;

	if (GET_MODE (XEXP (x, 0)) == QImode)
	  times = 1;
	else if (GET_MODE (XEXP (x, 0)) == HImode)
	  times = 3;
	else
	  return 1000;

	if (code0 == REG)
	  {
            return 1*times;
	  }
	else if (code0 == MEM)
	  {
            return 3*times;
	  }
      }
    case TRUNCATE:
    case SIGN_EXTEND:
    case ZERO_EXTEND:
      return 2;
    case MEM:
      return 2;
    }
  return 0;
}

void
unsp_asm_file_start (file)
     FILE *file;
{
  int i;
  extern int save_argc;
  extern char **save_argv;

  fprintf (file, "// GCC for SUNPLUS u'nSP version %s\n", UNSP_VERSION_STRING);
  fprintf (file, "// Command: ");
  for (i = 0; i < save_argc; i++)
    {
      fprintf (file, "%s", save_argv[i]);
      if (i + 1 < save_argc)
        fprintf (file, " ");
    }
  fprintf (file, "\n\t.external __sn_func_ptr_sec\n\n");
}

/* This is called at the end of assembly.  For each external function
   which has not been defined, we output a declaration now.  We also
   output the .drectve section.  */
void
unsp_asm_file_end (file)
     FILE *file;
{
  struct func_list *p, *q;
  struct var_sec_list *u, *v;
  tree decl;

  /* function memcpy don't declare.  */
  /* TREE_ASM_WRITTEN (get_identifier ("memcpy")) = 1; */

  for (p = extern_head; p != NULL; q = p->next, free (p), p = q)
    {
      decl = get_identifier (p->name);
      /* Positively ensure only one declaration for any given symbol.  */
      if (! TREE_ASM_WRITTEN (decl))
	{
	  TREE_ASM_WRITTEN (decl) = 1;
	  fprintf (file, ".external ");
	  if (strcmp (p->name, "memcpy") == 0)
	    assemble_name (file, "_BlockCopy");
	  else
            assemble_name (file, p->name);
	  fputs ("\n", file);
	}
      free (p->name);
    }

  for (p = exports_head; p != NULL; q = p->next, free (p), p = q)
    {
      decl = get_identifier (p->name);
      if (! TREE_ASM_WRITTEN (decl))
	{
	  TREE_ASM_WRITTEN (decl) = 1;
	  fprintf (file, ".external ");
          assemble_name (file, p->name);
	  fputs("\n", file);
	}
      free (p->name);
    }

  if (used_far_ptr_head != NULL)
    {
      char name[60];

      fprintf (file, "\n// far pointer entry table:\n");
      for (p = used_far_ptr_head; p != NULL; q = p->next, free (p), p = q)
        {
          if (TARGET_PAGE0_MASKROM)
            fprintf (file, "%s_ptsec: .section .nb_merge\n", p->name);
          else
            fprintf (file, "%s_ptsec: .section .vtbl\n", p->name);

          fprintf (file, "%s_entry:\t.dw seg _%s, offset _%s\n\n",
                         p->name, p->name, p->name);
          free (p->name);
        }
    }
  fprintf(file, "\t.end\n");

  for (p = far_ptr_head; p != NULL; q = p->next, free (p), p = q)
    {
      free (p->name);
    }

  for (u = var_sec_head; u != NULL; v = u->next, free (u), u = v)
    {
      free (u->var_name);
      free (u->sec_name);
    }
}

void
add_sec_var (var_name, sec_name)
    const char * var_name;
    const char * sec_name;
{
  struct var_sec_list *p;

  for (p = var_sec_head; p != NULL; p = p->next)
    if (strcmp (var_name, p->var_name) == 0)
      return;

  p = (struct var_sec_list *) malloc (sizeof *p);
  p->next = var_sec_head;
  p->var_name = (char *) malloc (strlen (var_name) + 1);
  strcpy (p->var_name, var_name);
  p->sec_name = (char *) malloc (strlen (sec_name) + 1);
  strcpy (p->sec_name, sec_name);
  var_sec_head = p;
}

void
asm_output_section_name (file, decl, name, reloc)
     FILE * file;
     tree decl;
     const char * name;
     int reloc ATTRIBUTE_UNUSED;
{
  if (TREE_CODE (decl) == VAR_DECL || TREE_CODE (decl) == CONST_DECL)
    fprintf (file, "%s\n", name);
  else
    warning ("section attribute \"%s\" discarded for non variable and non constant declaration \"%s\".",
             name, XSTR (XEXP (DECL_RTL (decl), 0), 0));
}

void
asm_output_float (file, fp_const)
     FILE *file;
     float fp_const;
{
#if HOST_FLOAT_FORMAT == TARGET_FLOAT_FORMAT
  REAL_VALUE_TYPE d = fp_const;
  int value;

  REAL_VALUE_TO_TARGET_SINGLE (d, value);
  fputs ("\t.dw ", file);

#if WORDS_BIG_ENDIAN > 0
  fprintf (file, "0x%-4.4x, 0x%-4.4x", (value >> 16) & 0xffff, (value & 0xffff));
#else
  fprintf (file, "0x%-4.4x, 0x%-4.4x", (value & 0xffff), (value >> 16) & 0xffff);
#endif

  fputs ("\n", file);

#else /* HOST_FLOAT_FORMAT != TARGET_FLOAT_FORMAT */
  fatal ("inline float constants not supported on this host");
#endif
}

#define ASCII_LENGTH 20
void
asm_output_ascii (file, ptr, length)
     FILE *file;
     char *ptr;
     int length;
{
  int i;
  int c;
  int output_packed_string = 0;
  int len;

  fprintf (asm_out_file, "\t.str ");

  if (ptr[0] == unsp_packed_string_prefix)
    {
#ifdef unSP
      len = strlen (ptr);
#else
      len = length * 2;
#endif
      fprintf (asm_out_file, "'@', ");
      ptr++;
      output_packed_string = 1;
    }
  else
    len = length;

  for (i = 0; i < len; i++)
    {
      c = ptr[i];

      if (output_packed_string
          && (i == len - 1)
	  && (ptr[i - 1] == 0))
        {
	  fprintf (asm_out_file, "%d", 0);
        }
      else if (c >= ' ' && c <= 0177 && c != '\'')
	{
          putc ('\'', asm_out_file);
          putc (c, asm_out_file);
          putc ('\'', asm_out_file);
	}
      else
	{
	  fprintf (asm_out_file, "%d", c & 0xff);
	}

      if (i == len - 1)
        {
          /* Empty */
        }
      else if ((i + 1) % ASCII_LENGTH == 0)
        {
          fprintf (asm_out_file, "\n\t.str ");
	  if (output_packed_string == 1)
            {
              fprintf (asm_out_file, "\'@\', ");
            }
        }
      else
        {
          fprintf (asm_out_file, ", ");
        }
    }
#ifdef unSP
  if (output_packed_string)
    if ((len & 1) == 0)
      fprintf (asm_out_file, ", 0, 0");
    else
      fprintf (asm_out_file, ", 0");
#endif

  fprintf (asm_out_file, "\n");
  fprintf (asm_out_file, "\t// length = %d\n", length);
}

void
asm_output_common (file, name, size, rounded)
     FILE *file;
     char *name;
     int size;
     int rounded;
{
  bss_section ();
  ASM_GLOBALIZE_LABEL (file, name);
  assemble_name (file, name);
  fputs (":", file);
  if (rounded > 1)
    fprintf(file, "\n\t.dw %d dup(0)\n", rounded);
  else
    fprintf(file, "\n\t.dw 0\n");
}

void
asm_output_local (file, name, size, rounded)
     FILE *file;
     char *name;
     int size;
     int rounded;
{
  bss_section ();
  assemble_name (file, name);
  fputs (":", file);
  if (rounded > 1)
    fprintf (file, "\n\t.dw %d dup(0)\n", rounded);
  else
    fprintf (file, "\n\t.dw 0\n");
}

void
unsp_register_far_ptr_name (name)
     const char *name;
{
  struct func_list *p;

  for (p = far_ptr_head; p; p = p->next)
    {
      if (strcmp (p->name, name) == 0)
        return;
    }

  p = (struct func_list *) malloc (sizeof *p);
  p->next = far_ptr_head;
  p->name = (char *) malloc (strlen (name) + 1);
  strcpy (p->name, name);
  far_ptr_head = p;
}

void
unsp_register_used_far_ptr_name (name)
     const char *name;
{
  struct func_list *p;

  for (p = used_far_ptr_head; p; p = p->next)
    {
      if (strcmp (p->name, name) == 0)
        return;
    }

  p = (struct func_list *) malloc (sizeof *p);
  p->next = used_far_ptr_head;
  p->name = (char *) malloc (strlen (name) + 1);
  strcpy (p->name, name);
  used_far_ptr_head = p;
}

int
far_ptr_name (fpname)
     const char *fpname;
{
  struct func_list *p;

  for (p = far_ptr_head; p != NULL; p = p->next)
    {
      if (strcmp (fpname, p->name) == 0)
        {
          unsp_register_used_far_ptr_name (fpname);
          return 1;
        }
    }
  return 0;
}

char *
var_sec_name (var_name)
     const char *var_name;
{
  struct var_sec_list *p;

  for (p = var_sec_head; p != NULL; p = p->next)
    {
      if (strcmp (var_name, p->var_name) == 0)
        {
          return p->sec_name;
        }
    }

  return NULL;
}

int
check_sec_var (operand, var_name, sec_name)
     rtx operand;
     char **var_name;
     char **sec_name;
{
  if (GET_CODE (operand) == SYMBOL_REF)
    {
      *var_name = XSTR (operand, 0);
      if (*sec_name = var_sec_name (*var_name))
        return 1;
      else
        return 0;
    }
  else if (GET_CODE (operand) == MEM)
    {
      rtx tmp = XEXP (operand, 0);

      if (GET_CODE (tmp) == CONST)
        tmp = XEXP (tmp, 0);

      if (GET_CODE (tmp) == SYMBOL_REF)
        {
          *var_name = XSTR (tmp, 0);
          if (*sec_name = var_sec_name (*var_name))
            return 1;
          else
            return 0;
        }
      else if (GET_CODE (tmp) == PLUS)
        {
          if (GET_CODE (XEXP (tmp, 0)) == SYMBOL_REF)
            {
              *var_name = XSTR (XEXP (tmp, 0), 0);
              if (*sec_name = var_sec_name (*var_name))
                return 1;
              else
                return 0;
            }
          else if (GET_CODE (XEXP (tmp, 1)) == SYMBOL_REF)
            {
              *var_name = XSTR (XEXP (tmp, 1), 0);
              if (*sec_name = var_sec_name (*var_name))
                return 1;
              else
                return 0;
            }
          else if (GET_CODE (XEXP (tmp, 0)) == REG
                   && GET_CODE (XEXP (tmp, 1)) == CONST_INT)
            return 0;
        }
      else if (GET_CODE (tmp) == REG
               || GET_CODE (tmp) == POST_INC
               || GET_CODE (tmp) == POST_DEC
               || GET_CODE (tmp) == PRE_INC
               || GET_CODE (tmp) == ADDRESSOF
               || GET_CODE (tmp) == CONST_INT)
        return 0;

#if 0
      debug_rtx (operand);
      exit (1);
#endif
    }
    return 0;
}

/* Assemble an external function reference.  We need to keep a list of
   these, so that we can output the function types at the end of the
   assembly.  We can't output the types now, because we might see a
   definition of the function later on and emit debugging information
   for it then.  */
void
asm_output_external (name)
     char *name;
{
  struct func_list *p;

  p = (struct func_list *) malloc (sizeof *p);
  p->next = extern_head;
  p->name = (char *) malloc (strlen (name) + 1);
  strcpy (p->name, name);
  extern_head = p;
}

/* Assemble an export symbol entry.  We need to keep a list of
   these, so that we can output the export list at the end of the
   assembly.  We used to output these export symbols in each function,
   but that causes problems with GNU ld when the sections are
   linkonce.  */
void
asm_output_external_libcall (func)
     rtx func;
{
  struct func_list *p;

  p = (struct func_list *) malloc (sizeof *p);
  p->next = exports_head;
  p->name = (char *) malloc (strlen (XSTR (func, 0)) + 1);
  strcpy (p->name, XSTR (func, 0));
  exports_head = p;
}

void
unsp_print_operand(file, op, letter)
     FILE *file;
     rtx op;
     int letter;
{
  enum rtx_code code = GET_CODE (op);

  switch (letter)
    {
    case 'C':
      switch (code)
	{
	case EQ:
	  fputs ("ne", file);
	  return;
	case NE:
	  fputs ("e", file);
	  return;
	case GT:
	  fputs ("le", file);
	  return;
	case GTU:
	  fputs ("be",file);
	  return;
	case LT:
	  fputs ("ge", file);
	  return;
	case LTU:
	  fputs ("ae",file);
	  return;
	case GE:
	  fputs ("l", file);
	  return;
	case GEU:
	  fputs ("b",file);
	  return;
	case LE:
	  fputs ("g", file);
	  return;
	case LEU:
	  fputs ("a",file);
	  return;
	default:
	  printf ("Invalid compare instruction %C .\n");
	  abort ();
	}
    case 'D':
      switch (code)
	{
	case EQ:
	  fputs ("e", file);
	  return;
	case NE:
	  fputs ("ne", file);
	  return;
	case GT:
	  fputs ("g", file);
	  return;
	case GTU:
	  fputs ("a", file);
	  return;
	case LT:
	  fputs ("l", file);
	  return;
	case LTU:
	  fputs ("b", file);
	  return;
	case GE:
	  fputs ("ge", file);
	  return;
	case GEU:
	  fputs ("ae", file);
	  return;
	case LE:
	  fputs ("le", file);
	  return;
	case LEU:
	  fputs ("be",file);
	  return;
	default:
	  printf ("Invalid compare instruction %D .\n");
	  abort ();
	}
    default:
      break;
    }

  if (code == REG)
    fprintf (file, "%s" , reg_names[REGNO (op)]);
  else if (code == MEM)
    output_address (XEXP (op, 0));
  else if (code == CONST_INT)
    {
      HOST_WIDE_INT val = INTVAL (op);
      if (val >= 0)
	fprintf (file, "%d", val);
      else if (val < 0)
	fprintf (file, "(-%d)", (-val));
    }
    /* shp add for symbol_ref and label_ref */
  else if (code == SYMBOL_REF)
    {
      char *sec_name;

#if 0
      if (TARGET_WARN_SEC_VAR
          && (sec_name = var_sec_name (XSTR (op, 0))))
        warning ("accessing variable \"%s\" in \"%s\" section.", XSTR (op, 0), sec_name);
#endif

      if (strcmp (XSTR (op, 0), "memcpy") == 0)
	fprintf(file ,"__BlockCopy" );
      else
	output_addr_const (file, op);
    }
  else
    output_addr_const (file, op);
}

/* Print a memory operand whose address is ADDR.  */
void
unsp_print_operand_address (file, addr)
     FILE *file;
     rtx addr;
{
  rtx offset;
  enum rtx_code code = GET_CODE (addr);

  putc ('[', file);

  switch (code)
    {
    case REG: /* register indirect addressing */
      fprintf (file, "%s", reg_names[REGNO (addr)]);
      break;
    case LABEL_REF:
      output_asm_label (addr);
      break;
    case SYMBOL_REF: /* direct addressing */
      output_addr_const (file, addr);
      break;
    case PLUS:
      offset = 0;
      /* direct addressing symbol_ref plus offset */
      if (GET_CODE (XEXP (addr, 0)) == SYMBOL_REF
	  && GET_CODE (XEXP (addr, 1)) == CONST_INT)
	{
	  addr = XEXP (addr, 0);
	  /* offset = XEXP (addr, 1); */
	  output_addr_const (file, addr);
	  putc (']', file);
	  return ;
	}
      else if (GET_CODE (XEXP (addr, 1)) == SYMBOL_REF
	       && GET_CODE (XEXP (addr, 0)) == CONST_INT)
	{
	  addr = XEXP (addr, 1);
	  /* offset = XEXP (addr, 0); */
	  output_addr_const (file, addr);
	  putc (']', file);
	  return ;
	}
      /* indirect addressing bp+offset */
      else if (REG_OK_FOR_BASE_P (XEXP (addr, 0)))
	{
	  int mayoff;

	  mayoff = XINT (XEXP (addr, 1), 0);
	  fprintf (file, "bp+%d", mayoff);
	  putc (']', file);
	  return ;
	}
      break;
    case CONST: /* indirect addressing symbol+offset */
    case CONST_INT:
      /* offset = 0; */
      output_addr_const(file, addr);
      break;
    case POST_INC:
    case POST_DEC:
    case PRE_INC:
      {
	rtx temp = XEXP (addr, 0);
	int regs_num;

	if (! REG_P (temp))
	  {
	    debug_rtx (addr);
	    abort ();
	  }
	regs_num = REGNO (temp);
	if (code == POST_INC)
	  fprintf (file, "%s++", reg_names[regs_num]);
	else if (code == POST_DEC)
	  fprintf (file, "%s--", reg_names[regs_num]);
	else
	  fprintf (file ,"++%s", reg_names[regs_num]);
	break;
      }
    default :
      fprintf (file, "Default : May be error !");
    }

  putc (']', file);
}

void
unsp_dbx_output_function_end(file, func)
     FILE *file;
     char *func;
{
  static int sym_lineno = 1;
  char buffer[256];

  if (write_symbols == DBX_DEBUG)
    {
      ASM_GENERATE_INTERNAL_LABEL (buffer, "LME", sym_lineno);
      fprintf (file, ".debug\n\t.dw \'");
      fprintf (file, ".stabf \',0,0\n");
      fprintf (file, "\t.dd ");
      assemble_name (file, buffer);
      putc ('-', file);
      assemble_name (file, XSTR (XEXP (
		     DECL_RTL (current_function_decl), 0), 0));
      putc ('\n', file);
      fprintf (file, "\t.dw ");
      /* aladdin */
      if (current_function_decl && UNSP_ISR_FLAG (current_function_decl))
        fprintf (file, "0x0d,0x0a\n.text\n");
      else
        fprintf (file, "0x0d,0x0a\n.code\n");
      force_data_section ();
      ASM_OUTPUT_INTERNAL_LABEL (file, "LME", sym_lineno);
      sym_lineno++;
    }
}

rtx
gen_compare_reg (code, x, y)
     enum rtx_code code;
     rtx x, y;
{
  enum machine_mode mode;

  mode = GET_MODE (x);

  if (GET_MODE_CLASS (mode) == MODE_FLOAT)
    {
    }
  else if (mode == QImode)
    {
      emit_insn (gen_rtx (SET, VOIDmode,
                          cc0_rtx, gen_rtx (COMPARE, mode, x, y)));
    }
  else if (mode == HImode)
    {
      if (code == GTU || code == GEU || code == LTU || code == LEU)
	{
          emit_insn (gen_rtx (SET, VOIDmode,
                              cc0_rtx, gen_rtx (COMPARE, mode, x, y)));

	}
      else
	{
	  emit_insn (gen_rtx (PARALLEL, VOIDmode,
			gen_rtvec (2,
				   gen_rtx (SET, VOIDmode, cc0_rtx,
				            gen_rtx (COMPARE, mode, x, y)),
				   gen_rtx (CLOBBER, VOIDmode,
					    gen_rtx (SCRATCH, HImode, 0)))));
	}
    }
  else
    fatal ("Invalid mode for integer comparison in gen_compare_reg");

  return cc0_rtx;
}

rtx
gen_test_reg (x)
     rtx x;
{
  enum machine_mode mode;

  mode = GET_MODE (x);

  if (mode == QImode)
    {
      emit_insn (gen_rtx (SET, VOIDmode, cc0_rtx, x));
    }
  else if (mode == HImode)
    {
      emit_insn (gen_rtx (SET, VOIDmode, cc0_rtx, x));
    }
  else
    fatal ("Invalid mode for integer test in gen_test_reg");

  return cc0_rtx;
}

void
gen_QImode_compare_branch(op, dest)
     rtx op;
     rtx dest;
{
  rtx xops[2];

  xops[0] = dest;
  xops[1] = gen_rtx_LABEL_REF (GET_MODE(dest), gen_label_rtx ());

  switch (GET_CODE (op))
    {
    case EQ:
      output_asm_insn ("JNZ %1\t// QImode EQ", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case NE:
      output_asm_insn ("JZ %1\t// QImode NE", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case GT:
      output_asm_insn ("JNG %1\t// QImode GT", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case GTU:
      output_asm_insn ("JNA %1\t// QImode GTU", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case LT:
      output_asm_insn ("JNL %1\t// QImode LT", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case LTU:
      output_asm_insn ("JNB %1\t// QImode LTU", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case GE:
      output_asm_insn ("JL %1\t// QImode GE", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case GEU:
      output_asm_insn ("JB %1\t// QImode GEU", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case LE:
      output_asm_insn ("JG %1\t// QImode LE", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    case LEU:
      output_asm_insn ("JA %1\t// QImode LEU", xops);
      output_asm_insn ("PC=%0\n%1:", xops);
      return;
    default:
      abort ();
    }
}

void
gen_HImode_compare_branch(op, dest)
     rtx op;
     rtx dest;
{
  rtx xops[5];

  xops[0] = unsp_compare_op0;
  xops[1] = unsp_compare_op1;
  xops[2] = dest;
  xops[3] = gen_rtx_LABEL_REF (GET_MODE(dest), gen_label_rtx ());
  xops[4] = gen_rtx_LABEL_REF (GET_MODE(dest), gen_label_rtx ());

  switch (GET_CODE (op))
    {
    case EQ:
      output_asm_insn ("JNZ %4\t// HImode EQ", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JNZ %4", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case NE:
      output_asm_insn ("JNZ %3\t// HImode NE", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JZ  %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case GT:
      output_asm_insn ("JG  %3\t// HImode GT", xops);
      output_asm_insn ("JNZ %4", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JNA %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case GTU:
      output_asm_insn ("JA  %3\t// HImode GTU", xops);
      output_asm_insn ("JNZ %4", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JNA %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case LT:
      output_asm_insn ("JL  %3\t// HImode LT", xops);
      output_asm_insn ("JNZ %4", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JNB %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case LTU:
      output_asm_insn ("JB  %3\t// HImode LTU", xops);
      output_asm_insn ("JNZ %4", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JNB %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case GE:
      output_asm_insn ("JL  %4\t// HImode GE", xops);
      output_asm_insn ("JNZ %3", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JB  %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case GEU:
      output_asm_insn ("JB  %4\t// HImode GEU", xops);
      output_asm_insn ("JNZ %3", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JB  %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case LE:
      output_asm_insn ("JG  %4\t// HImode LE", xops);
      output_asm_insn ("JNZ %3", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JA  %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    case LEU:
      output_asm_insn ("JA  %4\t// HImode LEU", xops);
      output_asm_insn ("JNZ %3", xops);
      output_asm_insn ("CMP %0,%1", xops);
      output_asm_insn ("JA  %4\n%3:", xops);
      output_asm_insn ("PC=%2\n%4:", xops);
      return;
    default:
      abort ();
    }
}

void
gen_HFmode_compare_branch(op, dest)
     rtx op;
     rtx dest;
{
  rtx xops[1];

  xops[0] = dest;

  switch (GET_CODE (op))
    {
    case EQ:
      output_asm_insn ("JNZ %0\t// HFmode EQ", xops);
      return;
    case NE:
      output_asm_insn ("JZ %0\t// HFmode NE", xops);
      return;
    case GT:
      output_asm_insn ("JLE %0\t// HFmode GT", xops);
      return;
    case LT:
      output_asm_insn ("JGE %0\t// HFmode LT", xops);
      return;
    case GE:
      output_asm_insn ("JL %0\t// HFmode GE", xops);
      return;
    case LE:
      output_asm_insn ("JG %0\t// HFmode LE", xops);
      return;
    default:
      abort ();
    }
}

void
gen_compare_branch(op, dest)
     rtx op;
     rtx dest;
{
      if (unsp_compare_mode == QImode)
        {
          gen_QImode_compare_branch (op, dest);
        }
      else if (unsp_compare_mode == HImode)
        {
          gen_HImode_compare_branch (op, dest);
        }
      else if (unsp_compare_mode == HFmode)
        {
          gen_HFmode_compare_branch (op, dest);
        }
/*
      else if (unsp_compare_mode == VOIDmode)
        {
          gen_QImode_compare_branch (op, dest);
        }
*/
      else
        {
          abort ();
        }
}

/* Return nonzero if IDENTIFIER with arguments ARGS is a valid machine specific
   attribute for TYPE.  The attributes in ATTRIBUTES have previously been
   assigned to DECL.  */
/*
int
unsp_valid_type_attribute_p (type, attributes, identifier, args)
     tree type;
     tree attributes;
     tree identifier;
     tree args;
{
  if (TREE_CODE (type) != FUNCTION_TYPE
      && TREE_CODE (type) != FIELD_DECL
      && TREE_CODE (type) != TYPE_DECL)
    return 0;

  if (is_attribute_p ("far", identifier))
    {
      return (args == NULL_TREE);
    }

  return 0;
}
*/

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.  */
/*
void
init_cumulative_args (cum, fntype, libname, incoming)
     CUMULATIVE_ARGS *cum;
     tree fntype;
     rtx libname;
     int incoming;
{
  *cum = 0;

  if (fntype && lookup_attribute ("far", TYPE_ATTRIBUTES (fntype)))
    unsp_register_far_ptr_name (IDENTIFIER_POINTER (TYPE_NAME (fntype)));
}
*/
