/* Definitions of target machine for GNU compiler, for SUNPLUS u'nSP.
   Copyright (C) 1992-2000 Free Software Foundation, Inc.
   Contributed by Tim Ouyang (tim_ouyang@sunplus.com.tw)

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

#define unSP 1
#define HAVE_cc0
#define UNSP_VERSION_STRING "1.0.12"

extern int rtx_equal_function_value_matters;

struct unsp_frame_info
{
  unsigned int total_size;      /* # words that the entire frame takes up */
  unsigned int var_size;        /* # words that variables take up */
  unsigned int reg_size;        /* # words needed to store regs */
  int          initialized;     /* != 0 if frame size already calculated */
  int          function_makes_calls;  /* Does the function make calls */
};

extern struct unsp_frame_info current_frame_info;

extern enum machine_mode unsp_compare_mode;
extern struct rtx_def *unsp_compare_op0, *unsp_compare_op1;
extern void gen_compare_branch ();

extern char unsp_tmpstr[];

/*
  Controlling the compilation driver, "gcc"
*/

#ifndef CC1_SPEC
#define CC1_SPEC "                    \
%{mbig5:-fkeep-inline-functions}      \
%{mnobig5:-fkeep-inline-functions}"
#endif

#ifndef CPP_SPEC
#define CPP_SPEC "            \
%{!mnobig5:-mbig5}            \
%{!mpc=*:-D __PREFIX_CHAR__=64} \
%{mpc=*:-D __PREFIX_CHAR__=%*unSP}"
#endif

#ifndef SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS
#endif

/*
  Run-time target specification
*/

#define CPP_PREDEFINES "-DunSP"

/* FAR usage:
   ¦pªG¼g¦bÅÜ¼Æ«e­±
   «h¬O¹ï«¬§O§@­×§ï, ¦pªG¬O¼g¦bÅÜ¼Æ«á­±, «h¬O¥u¹ïÅÜ¼Æ§@­×§ï
   
   int FAR *a, *b, c;  a,b ¬O FAR, c ¬O int
   int * a FAR, *b;    a ¬O FAR, b ¬O near
   int * a, FAR *b, *c; a ¬O near, b,c ¬O FAR  */

extern int target_flags;

/* Output extra debug info */
#define MASK_WARN_SEC_VAR   0x0001
#define MASK_BIG5_ESC_SEQ   0x0002
#define MASK_DEBUG_UNSP_GCC 0x8000

#define TARGET_WARN_SEC_VAR   (target_flags & MASK_WARN_SEC_VAR)
#define TARGET_BIG5_ESC_SEQ   (target_flags & MASK_BIG5_ESC_SEQ)
#define TARGET_DEBUG_UNSP_GCC (target_flags & MASK_DEBUG_UNSP_GCC)

#define TARGET_SWITCHES				\
{						\
  {"warn-sec-var", MASK_WARN_SEC_VAR, 		\
     "Generate warning when accessing variable in named section"}, \
  {"big5", MASK_BIG5_ESC_SEQ, 			\
     "Handle embedded escape characters in zh_TW.Big5 encoding"}, \
  {"nobig5", -MASK_BIG5_ESC_SEQ, 		\
     "Don't handle embedded escape characters in zh_TW.Big5 encoding"}, \
  {"debug", MASK_DEBUG_UNSP_GCC, 		\
     "Output extra GCC debug information"},	\
  SUBTARGET_SWITCHES                            \
  {"", TARGET_DEFAULT,                          \
     NULL}					\
}

extern const char *unsp_packed_string_prefix_string;
extern char unsp_packed_string_prefix;

#ifndef TARGET_DEFAULT
#define TARGET_DEFAULT MASK_BIG5_ESC_SEQ
#endif

#define TARGET_OPTIONS                             \
{                                                  \
  { "pc=", &unsp_packed_string_prefix_string,      \
     "Specify the prefix char for packed string"}, \
  SUBTARGET_OPTIONS                                \
}

#define SUBTARGET_SWITCHES
#define SUBTARGET_OPTIONS

#define OVERRIDE_OPTIONS override_options ()

#if !defined(__DATE__)
  #define TARGET_VERSION fprintf (stderr, " (%s)", VERSION_INFO)
#else
  #define TARGET_VERSION fprintf (stderr, " (%s, %s)", VERSION_INFO, __DATE__)
#endif
#define VERSION_INFO "SUNPLUS u'nSP(alpha)"

/* aladdin 
 * Add for ISR function attribute
 */
#define UNSP_ISR_FLAG TREE_LANG_FLAG_0

/* If this macro is defined, GNU CC gathers statistics about 
   the number and kind of tree node it allocates during each 
   run. The option '-fstats' will tell the compiler to print 
   these statistics about the sizes of it obstacks.  */
/* This macro is undocumented in the "Using and Posting the
   GNU Compiler Collection".  */   
#define GATHER_STATISTICS

/*
  Storage layout
*/

/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.  */
#define BITS_BIG_ENDIAN 0

/* Define this if most significant byte of a word is the lowest numbered.  */
#define BYTES_BIG_ENDIAN 0

/* Define this if most significant word of a multiword number is numbered.  */
#define WORDS_BIG_ENDIAN 0

/* number of bits in an addressable storage unit */
#define BITS_PER_UNIT 16

/* Width in bits of a "word", which is the contents of a machine register.
   Note that this is not necessarily the width of data type `int';
   if using 16-bit ints on a 68000, this would still be 32.
   But on a machine with 16-bit registers, this would be 16.  */
#define BITS_PER_WORD 16

/* Maximum number of bits in a word. */
#define MAX_BITS_PER_WORD 16

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 1

/* Width in bits of a pointer.
   See also the macro `Pmode' defined below.  */
#define POINTER_SIZE 16

/* Define this macro if it is advisable to hold scalars in registers
   in a wider mode than that declared by the program.  In such cases,
   the value is constrained to be within the bounds of the declared
   type, but kept valid in the wider mode.  The signedness of the
   extension may differ from that of the type.

   We promote any value smaller than SImode up to SImode.  We don't
   want to promote to DImode when in 64 bit mode, because that would
   prevent us from using the faster SImode multiply and divide
   instructions.  */
   
/* Following define is mips.h
#define PROMOTE_MODE(MODE, UNSIGNEDP, TYPE)     \
  if (GET_MODE_CLASS (MODE) == MODE_INT         \
      && GET_MODE_SIZE (MODE) < 4)              \
		    (MODE) = SImode; 
*/

/* 
#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE)	\
  if (GET_MODE_CLASS(MODE)==MODE_INT		\
      && GET_MODE_SIZE (MODE )<4 )		\
      		(MODE)=HImode ;
*/				    
/*
#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE)	QImode
*/

/* Define this if function arguments should also be promoted using 
   the above procedure.  */
#define PROMOTE_FUNCTION_ARGS
   
/* Likewise, if the function return value is promoted.  */
#define PROMOTE_FUNCTION_RETURN

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY 16

/* Boundary (in *bits*) on which stack pointer should be aligned.  */
#define STACK_BOUNDARY 16

/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY 16

/* Biggest alignment that any data type can require on this machine, in bits. */
#define BIGGEST_ALIGNMENT 16

/* If defined, the smallest alignment, in bits, that can be given to 
   an object that can be referenced in one operation, without disturbing 
   any nearby object.  Normally, this is BITS_PER_UNIT, but may be larger 
   on machines that don't have byte or half-word store operations.  */
#define MINIMUM_ATOMIC_ALIGNMENT 16

/* Biggest alignment that any structure field can require on
   this machine, in bits */
#define BIGGEST_FIELD_ALIGNMENT 16

/* Alignment of field after `int : 0' in a structure.  */
#define EMPTY_FIELD_BOUNDARY 16

/* Number of bits which any structure or union's size must be a multiple of.
   Each structure or union's size is rounded up to a multiple of this */
#define STRUCTURE_SIZE_BOUNDARY 16

/* Set this none-zero if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT 0
/*
#define STRICT_ALIGNMENT 1
*/

/* If bit field type is int, don't let it cross an int, and give
   entire struct the alignment of an int.  */
#define PCC_BITFIELD_TYPE_MATTERS 1

/* An integer expression for the size in bits of the largest
   integer machine mode that should actually be used. All
   integer machine modes of this size or smaller can be
   used for structures and unions with the appropriate sizes.  */
#define MAX_FIXED_MODE_SIZE 32
/* 32 = GET_MODE_BITSIZE (HImode) */

#define TARGET_FLOAT_FORMAT IEEE_FLOAT_FORMAT

/*
  Layout of source language data types
*/

/* Setting a type size which is smaller than BITS_PER_UNIT will
   be rounded to BITS_PER_UNIT */
#define CHAR_TYPE_SIZE          16
#define SHORT_TYPE_SIZE         16
#define INT_TYPE_SIZE           16
#define LONG_TYPE_SIZE          32
#define LONG_LONG_TYPE_SIZE     32

#define FLOAT_TYPE_SIZE         32
#define DOUBLE_TYPE_SIZE        32
#define LONG_DOUBLE_TYPE_SIZE   32

/* An expression whose value is 1 or 0, according to whether the type char
   should be signed or unsigned by default.  */
/* 1 for signed and 0 for unsigned */
#define DEFAULT_SIGNED_CHAR 1

/* A C expression to determine whether to give an enum type only as many bytes
   as it takes to represent the range of possible values of that type. A nonzero
   value means to do that; a zero value means all enum types should be allocated
   like int.  */
/* meaningless here since short and int are the same size.  */
#define DEFAULT_SHORT_ENUMS 0

/* A C expression for a string describing the name of the data type
   to use for size values.  */
/* Defaut is "long unsigned int" if we dont define it.  */
#define SIZE_TYPE "unsigned int"

/* A C expression for a string describing the name of the data type
   to use for the result of subtracting two pointers */
/* Defaut is "long int" if we dont define it.  */
#define PTRDIFF_TYPE "int"

/* A C expression for a string describing the name of the data type
   to use for wide characters.  */
/* Defaut is "int" if we dont define it.  */
#define WCHAR_TYPE "int"

/* A C expression for the size in bits of the data type for wide characters.
   This is used in cpp.  */
#define WCHAR_TYPE_SIZE 16

/* Define results of standard character escape sequences.  */
#define TARGET_BELL    007
#define TARGET_BS      010
#define TARGET_TAB     011
#define TARGET_NEWLINE 012
#define TARGET_VT      013
#define TARGET_FF      014
#define TARGET_CR      015

/*
  Register usage
*/

#define REG_SP  0
#define REG_R1  1
#define REG_R2  2
#define REG_R3  3
#define REG_R4  4
#define REG_REAL_BP 5
#define REG_SOFT_BP 6
#define REG_SOFT_AP 7

/*
  Basic characteristics of registers
*/

#define FIRST_PSEUDO_REGISTER 8

#define FIXED_REGISTERS         \
  { 1, 0, 0, 0, 0,  0,  0,  0}
/* SP,R1,R2,R3,R4,RBP,SBP,SAP */

#define CALL_USED_REGISTERS     \
  { 1, 1, 1, 1, 1,  0,  0,  0 }
/* SP,R1,R2,R3,R4,RBP,SBP,SAP */

/*
  Order of allocation of registers
*/

#define REG_ALLOC_ORDER         	\
  { REG_R1, REG_R2, REG_R3, REG_R4,	\
    REG_REAL_BP, REG_SP, REG_SOFT_BP, REG_SOFT_AP }


/*
  How values fit in registers
*/

/* On a machine where all registers are exactly one word,
   a suitable definition of this macro is */
#define HARD_REGNO_NREGS(REGNO,MODE) \
  ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

/* None zero of a value of MODE fits into one or more registers
   starting with REGNO.  */
#define HARD_REGNO_MODE_OK(REGNO,MODE) 			\
  ((MODE == HImode || MODE == HFmode)			\
   ? ((REGNO == REG_R1 || REGNO == REG_R3) ? 1 : 0) 	\
   : ((MODE == QImode || MODE == VOIDmode) ? 1 : 0)) 
/*
#define HARD_REGNO_MODE_OK(REGNO,MODE) 			\
  ((MODE == HImode || MODE == HFmode)			\
   ? ((REGNO >= REG_R1 && REGNO <= REG_R3) ? 1 : 0) 	\
   : ((MODE == QImode || MODE == VOIDmode) ? 1 : 0)) 
#define HARD_REGNO_MODE_OK(REGNO, MODE) 1
*/

/* States whether it is desirable to choose the same register to
   avoid move-type instructions between different modes. This is
   desirable for compact code.  */
/* If HARD_REGNO_MODE_OK(r, mode1) and HARD_REGNO_MODE_OK(r, mode2)
   are always the same for any r, the MODES_TIEABLE_P(mode1, mode2)
   should be nonzero.  */
#define MODES_TIEABLE_P(MODE1, MODE2) 1
/*   
#define MODES_TIEABLE_P(MODE1,MODE2) 			\
	(MODE1 == MODE2  				\
	 || (GET_MODE_CLASS (MODE1) == MODE_FLOAT	\
	     && GET_MODE_CLASS (MODE2) == MODE_FLOAT))
*/

/*
  Handling leaf functions
*/

/* No special treatment needed */
/* Whether this is good or bad, I don't know.  */

/*
  Registers that form a stack
*/

/* This is to support registers like a stack, such as the floating
   point registers in 80387.  */
/* no need here */

/*
  Register classes
*/

/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.

   One of the classes must always be named ALL_REGS and include all hard regs.
   If there is more than one class, another class must be named NO_REGS
   and contain no registers.

   The name GENERAL_REGS must be the name of a class (or an alias for
   another name such as ALL_REGS).  This is the class of registers
   that is allowed by "g" or "r" in a register constraint.
   Also, registers outside this class are allocated only when
   instructions express preferences for them.

   The classes must be numbered in nondecreasing order; that is,
   a larger-numbered class must never be contained completely
   in a smaller-numbered class.

   For any two classes, it is very desirable that there be another
   class that represents their union.  */
/* u'nSP has a Base+#IM6 addressing mode. Other than this, all registers
   are treated as the same.  */
/* FIXME:
   The u'nSP opcode orthogonal-ness is still not know as of 20001025 */
enum reg_class {
  NO_REGS,
  R1R2_REGS,
  R3_REGS,
  R4_REGS,
  MUL_REGS,
  BASE_REGS,
  GP_REGS,
  ALL_REGS,
  LIM_REG_CLASSES
};

/* GENERAL_REGS must be the name of a register class */
#define GENERAL_REGS ALL_REGS

#define N_REG_CLASSES (int) LIM_REG_CLASSES

/* Give names of register classes as strings for dump file.   */
#define REG_CLASS_NAMES \
{                       \
  "NO_REGS",            \
  "R1R2_REGS",          \
  "R3_REGS",            \
  "R4_REGS",            \
  "MUL_REGS",           \
  "BASE_REGS",		\
  "GP_REGS",       	\
  "ALL_REGS"            \
}

/* Define which registers fit in which classes.
   This is an initializer for a vector of HARD_REG_SET
   of length N_REG_CLASSES.  */
#define REG_CLASS_CONTENTS      \
{                               \
  0x0000, /* NO_REGS */         \
  0x0006, /* R1R2_REGS */       \
  0x0008, /* R3_REGS */         \
  0x0010, /* R4_REGS */         \
  0x0018, /* MUL_REGS */        \
  0x00E0, /* BASE_REGS */		\
  0x001E, /* GP_REGS */		\
  0x00FF  /* ALL_REGS */        \
}

/* A C expression whose value is a register class containing hard
   register REGNO.  In general there is more that one such class;
   choose a class which is "minimal", meaning that no smaller class
   also contains the register.  */
#define REGNO_REG_CLASS(REGNO)          \
 ((REGNO) == REG_SP ? ALL_REGS  :       \
  (REGNO) == REG_R1 ? R1R2_REGS :       \
  (REGNO) == REG_R2 ? R1R2_REGS :	\
  (REGNO) == REG_R3 ? R3_REGS   :	\
  (REGNO) == REG_R4 ? R4_REGS   :	\
  (REGNO) == REG_REAL_BP ? BASE_REGS :	\
  (REGNO) == FRAME_POINTER_REGNUM ? BASE_REGS :	\
  (REGNO) == ARG_POINTER_REGNUM   ? BASE_REGS : NO_REGS)

/* A macro whose definition is the name of the class to which a
   valid base register must belong.  A base register is one used in
   an address which is the register value plus a displacement.  */
#define BASE_REG_CLASS ALL_REGS

/* A macro whose definition is the name of the class to which a
   valid index register must belong.  An index register is one used
   in an address where its value is either multiplied by a scale
   factor or added to another register (as well as added to a
   displacement).  */
#define INDEX_REG_CLASS NO_REGS

/* Get reg_class from a letter such as appears in the machine
   description.  The register letter `r', corresponding to class
   GENERAL_REGS, will not be passed to this macro.

   DEFINED REGISTER CLASSES:
   'b'  GCC base registers
*/
#define REG_CLASS_FROM_LETTER(C)        \
  ((C) == 'c' ? R3_REGS   :             \
   (C) == 'd' ? R4_REGS   :             \
   (C) == 'e' ? MUL_REGS  :             \
   (C) == 'h' ? R1R2_REGS :		\
   (C) == 'f' ? GP_REGS   : NO_REGS)

/* A C expression which is nonzero if register REGNO is suitable for use
   as a base register in operand addresses.  It may be either a suitable
   hard register or a pseudo register that has been allocated such a
   hard register.  */
#define REGNO_OK_FOR_BASE_P(NUM)	\
  ((NUM) == REG_REAL_BP 		\
   || (NUM) == FRAME_POINTER_REGNUM 	\
   || (NUM) == ARG_POINTER_REGNUM)


/* Similar for index registers.  */
#define REGNO_OK_FOR_INDEX_P(NUM) 0

/* Given an rtx X being reloaded into a reg required to be
   in class CLASS, return the class of reg to actually use.
   In general this is just CLASS; but on some machines
   in some cases it is preferable to use a more restrictive class.  */
#define PREFERRED_RELOAD_CLASS(X,CLASS) (CLASS)	

/* When defined, the compiler allows registers explicitly used in the
   rtl to be used as spill registers but prevents the compiler from
   extending the lifetime of these registers.  */
#define SMALL_REGISTER_CLASSES 1

/* A C expression whose value is nonzero if pseudos that have been
   assigned to registers of class CLASS would likely be spilled
   because registers of CLASS are needed for spill registers.

   The default value of this macro returns 1 if CLASS has exactly one
   register and zero otherwise.  On most machines, this default
   should be used.  Only define this macro to some other expression
   if pseudo allocated by `local-alloc.c' end up in memory because
   their hard registers were needed for spill registers.  If this
   macro returns nonzero for those classes, those pseudos will only
   be allocated by `global.c', which knows how to reallocate the
   pseudo to another register.  If there would not be another
   register available for reallocation, you should not change the
   definition of this macro since the only effect of such a
   definition would be to slow down register allocation.  */	
/*
#define CLASS_LIKELY_SPILLED_P(CLASS) 	\
  ((CLASS) == R3_REGS			\
   || (CLASS) == R4_REGS		\
   || (CLASS) == MUL_REGS		\
   || (CLASS) == BP_REGS		\
   || (CLASS) == GP_REGS)
*/
/* #define CLASS_LIKELY_SPILLED_P(CLASS) 1 */

/*
#define CLASS_LIKELY_SPILLED_P(CLASS)	\
  ((CLASS == R1_REG)			\
    || (CLASS == R2_REG)		\
    || (CLASS == R3_REG) 		\
    || (CLASS == R4_REG) 		\
    || (CLASS == RL1_REGS)		\
    || (CLASS == RL2_REGS))
*/

/* Return the maximum number of consecutive registers
   needed to represent mode MODE in a register of class CLASS.
   On the u'nSP, this is the size of MODE in words,
   since class doesn't make any difference. */
#define CLASS_MAX_NREGS(CLASS,MODE) GET_MODE_SIZE(MODE)
/*
#define CLASS_MAX_NREGS(CLASS,MODE) 					\
  (MODE == QImode || MODE == VOIDmode) ? 1 :				\
  ((MODE == HImode || MODE == HFmode) && (CLASS == GP_REGS)) ? 1 :	\
  (MODE == SImode) ? 4 : 2
*/
/*
#define CLASS_MAX_NREGS(CLASS,MODE) \
  (MODE == QImode || MODE == VOIDmode) ? 1 :
  ((MODE == HImode || MODE == HFmode) && CLASS == GP_REGS) : 1
  (MODE == HImode || MODE == HFmode) ? 2 :
  (MODE == SImode) ? 4 
*/

/* The letters I, J, K, L, M, N, O, and P in a register constraint
   string can be used to stand for particular ranges of immediate
   operands.  This macro defines what the ranges are.  C is the
   letter, and VALUE is a constant value.  Return 1 if VALUE is
   in the range specified by C.  */
/* For u'nSP:
   `I'  is used for immediate 6-bit values.
   `J'  is used for the range of number of shifts.
   `K'  is used for the range of general immediate values (16-bit).  */
#define CONST_OK_FOR_LETTER_P(VALUE, C)                 \
  ((C) == 'I' ? (VALUE) >= 0 && (VALUE) <=    63 :      \
   (C) == 'J' ? (VALUE) >= 1 && (VALUE) <=     4 :      \
   (C) == 'K' ? (VALUE) >= 0 && (VALUE) <= 65535 : 0)

/* Similar, but for floating constants, and defining letters G and H.
   Here VALUE is the CONST_DOUBLE rtx itself.  */
#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C) 1

/* Letters in the range `Q' through `U' may be defined in a
   machine-dependent fashion to stand for arbitrary operand types.
   The machine description macro `EXTRA_CONSTRAINT' is passed the
   operand as its first argument and the constraint letter as its
   second operand.  */
#define EXTRA_CONSTRAINT(OP,C)				\
  ((C) == 'Q' ? direct16_memory_operand(OP, VOIDmode) :		\
   (C) == 'R' ? non_direct16_memory_operand(OP, VOIDmode) :	\
   (C) == 'S' ? lvalue_operand(OP, VOIDmode) : 0)
extern int direct16_memory_operand ();
extern int non_direct16_memory_operand ();
extern int lvalue_operand ();
/*
#define EXTRA_CONSTRAINT(OP, C)                           \
	((C) == 'R' ? symbolic_address_p(OP)  :           \
	 (C) == 'P' ? part_memory_operand(OP) : 0)
extern int symbolic_address_p ();
extern int part_memory_operand ();
*/

/*
  Basic stack layout
*/

/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD

/* Define this macro if the addresses of local variable slots 
   are at negative offsets from the frame pointer.  */
/* #define FRAME_GROWS_DOWNWARD */

/* Define this macro if successive arguments to a function 
   occupy decreasing addresses on the stack.  */
/* #define ARGS_GROW_DOWNWARD */

/* We use post decrement on the u'nSP because there isn't
   a pre-decrement addressing mode.  This means that we
   assume the stack pointer always points at the next
   FREE location on the stack.  */
/* This macro is undocumented in the "Using and Posting the
   GNU Compiler Collection".  */
#define STACK_PUSH_CODE POST_DEC 

/* Offset from the frame pointer to the first local variable slot 
   to be allocated.  If FRAME_GROWS_DOWNWARD, find the next slot's
   offset by subtracting the first slot's length from 
   STARTING_FRAME_OFFSET.  Otherwise, it is found by adding the 
   length of the first slot to the value STARTING_FRAME_OFFSET.  */
#define STARTING_FRAME_OFFSET 0

/* Offset from the stack pointer register to the first location at
   which outgoing arguments are placed.  */
/* This seems nonsense because outgoing arguments are placed at r1 */
#define STACK_POINTER_OFFSET 0

/* Offset from the argument pointer register to the 
   first argument's address.  */
#define FIRST_PARM_OFFSET(FNDECL) 0

/* A C expression whose value is RTL representing the value of the
   return address for the frame COUNT steps up from the current frame,
   after the prologue.  FRAMEADDR is the frame pointer of the COUNT
   frame, or the frame pointer of the COUNT - 1 frame if
   `RETURN_ADDR_IN_PREVIOUS_FRAME' is defined.  */
/* After the prologue, RA is at [FRAME] (that is, [BP])
   in the current frame.  */
#define RETURN_ADDR_RTX(COUNT, FRAME)			\
  ((COUNT) == 0						\
   ? gen_rtx_MEM (Pmode, gen_rtx_PLUS (   		\
                  Pmode, arg_pointer_rtx, GEN_INT (0)))	\
   : gen_rtx_MEM (Pmode, gen_rtx_PLUS (Pmode, (FRAME), GEN_INT (0))))
/*
#define RETURN_ADDR_RTX(COUNT, FRAME)                           \
  (COUNT == 0                                                   \
   ? gen_rtx (MEM, Pmode,                                       \
	      gen_rtx (PLUS, Pmode, (FRAME), GEN_INT(0)))       \
   : NULL_RTX)
*/

/* A C expression whose value is RTL representing the location of the
   incoming return address at the beginning of any function, before
   the prologue.  This RTL is either a `REG', indicating that the
   return value is saved in `REG', or a `MEM' representing a location
   in the stack.

   You only need to define this macro if you want to support call
   frame debugging information like that provided by DWARF 2.  */
/* Before the prologue, RA is at [SP+2].  */
#define INCOMING_RETURN_ADDR_RTX                                \
   gen_rtx (MEM, VOIDmode, gen_rtx (PLUS, VOIDmode,             \
	    gen_rtx (REG, VOIDmode, STACK_POINTER_REGNUM), GEN_INT(2)))

/* A C expression whose value is an integer giving the offset, in
   bytes, from the value of the stack pointer register to the top of
   the stack frame at the beginning of any function, before the
   prologue.  The top of the frame is defined to be the value of the
   stack pointer in the previous frame, just before the call
   instruction.

   You only need to define this macro if you want to support call
   frame debugging information like that provided by DWARF 2. */
#define INCOMING_FRAME_SP_OFFSET 0

/*
  Registers that address the stack frame
*/

/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM REG_SP

/* Base register for access to local variables of the function.  */
#define FRAME_POINTER_REGNUM REG_SOFT_BP

/* Define this to be where the real frame pointer is if it is not possible to
   work out the offset between the frame pointer and the automatic variables
   until after register allocation has taken place.  FRAME_POINTER_REGNUM
   should point to a special register that we will make sure is eliminated. */
#define HARD_FRAME_POINTER_REGNUM REG_REAL_BP

/* Base register for access to arguments of the function.  */
#define ARG_POINTER_REGNUM REG_SOFT_AP

/* Register in which static-chain is passed to a function.  */
/* FIXME: I don't know whether this is correct */
#define STATIC_CHAIN_REGNUM REG_R1

/*
  Eliminating frame pointer and arg pointer
*/

/* A C expression which is nonzero if a function must have and use a
   frame pointer. If its value is nonzero the functions will have a
   frame pointer. */
#define FRAME_POINTER_REQUIRED 1

/* A C statement to store in the variable 'DEPTH' the difference
   between the frame pointer and the stack pointer values immediately
   after the function prologue.  */
#define INITIAL_FRAME_POINTER_OFFSET(DEPTH) ((DEPTH) = 1)

/* If defined, this macro specifies a table of register pairs used to
   eliminate unneeded registers that point into the stack frame.  If
   it is not defined, the only elimination attempted by the compiler
   is to replace references to the frame pointer with references to
   the stack pointer.

   The definition of this macro is a list of structure
   initializations, each of which specifies an original and
   replacement register.

   On some machines, the position of the argument pointer is not
   known until the compilation is completed.  In such a case, a
   separate hard register must be used for the argument pointer.
   This register can be eliminated by replacing it with either the
   frame pointer or the argument pointer, depending on whether or not
   the frame pointer has been eliminated.

   In this case, you might specify:
	#define ELIMINABLE_REGS  \
	{{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
	 {ARG_POINTER_REGNUM, FRAME_POINTER_REGNUM}, \
	 {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}

   Note that the elimination of the argument pointer with the stack
   pointer is specified first since that is the preferred elimination.  */
#define ELIMINABLE_REGS         			\
  {{ARG_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM},	\
   {FRAME_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM},	\
   {ARG_POINTER_REGNUM, STACK_POINTER_REGNUM},		\
   {FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}}
   
/* A C expression that returns non-zero if the compiler is allowed to
   try to replace register number FROM-REG with register number
   TO-REG.  This macro need only be defined if `ELIMINABLE_REGS' is
   defined, and will usually be the constant 1, since most of the
   cases preventing register elimination are things that the compiler
   already knows about.  */
#define CAN_ELIMINATE(FROM, TO) \
  ((((FROM) == ARG_POINTER_REGNUM || (FROM) == FRAME_POINTER_REGNUM) && (TO) == HARD_FRAME_POINTER_REGNUM) \
   || (((FROM) == ARG_POINTER_REGNUM || (FROM) == FRAME_POINTER_REGNUM) && (TO) == STACK_POINTER_REGNUM))

/* This macro is similar to `INITIAL_FRAME_POINTER_OFFSET'.  It
   specifies the initial difference between the specified pair of
   registers.  This macro must be defined if `ELIMINABLE_REGS' is
   defined.  */
#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET) \
  ((OFFSET) = initial_elimination_offset (FROM, TO))
extern int initial_elimination_offset ();

/*
  Passing function arguments on the stack
*/

/* If we generate an insn to push BYTES bytes,
   this says how many the stack pointer really advances by.
   Note: what GCC calls a "byte" is really a 16-bit word,
   because BITS_PER_UNIT is 16.  */
#define PUSH_ROUNDING(BYTES) (BYTES)

/* Value is 1 if returning from a function call automatically
   pops the arguments described by the number-of-args field in the call.
   FUNDECL is the declaration node of the function (as a tree),
   FUNTYPE is the data type of the function (as a tree),
   or for a library call it is an identifier node for the subroutine name.  */
#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,SIZE) 0

/*
  Passing arguments in registers
*/

/* Define where to put the arguments to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   MODE is the argument's machine mode.
   TYPE is the data type of the argument (as a tree).
     This is null for libcalls where that information may
     not be available.
   CUM is a variable of type CUMULATIVE_ARGS which gives info about
     the preceding args and about the function being called.
   NAMED is nonzero if this argument is a named parameter
     (otherwise it is an extra parameter matching an ellipsis).  */
#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) 0

/* Define as a C expression that evaluates to nonzero if 
   we do not know how to pass TYPE solely in registers. 
   The file `expr.h' defines a definition that is usually 
   appropriate, refer to `expr.h' for additional documentation.  */
#define MUST_PASS_IN_STACK(MODE, TYPE) 1

/* For an arg passed partly in registers and partly in memory,
   this is the number of registers used.  For args passed
   entirely in registers or entirely in memory, zero.  */
#define FUNCTION_ARG_PARTIAL_NREGS(CUM, MODE, TYPE, NAMED) 0

/* This indicates that an argument is to be passed with an invisible
   reference (i.e., a pointer to the object is passed).  */
#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED) \
  (TYPE && AGGREGATE_TYPE_P (TYPE))

/* Define a data type for recording info about an argument list
   during the scan of that argument list.  This data type should
   hold all necessary information about the function itself
   and about the args processed so far, enough to enable macros
   such as FUNCTION_ARG to determine where the next arg should go.  */
#define CUMULATIVE_ARGS int

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.  */
#define INIT_CUMULATIVE_ARGS(CUM,FNTYPE,LIBNAME,INDIRECT) (CUM=0)

/* Update the data in CUM to advance over an argument
   of mode MODE and data type TYPE.  */
/* u'nSP pass every argument in stack. Define it to be empty.  */
#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED)

/* 1 if N is a possible register number for function argument passing.  */
#define FUNCTION_ARG_REGNO_P(N) 0

/*
  How scalar function values are returned
*/

/* Define how to find the value returned by a function.
   VALTYPE is the data type of the value (as a tree).
   If the precise function being called is known, FUNC is its FUNCTION_DECL;
   otherwise, FUNC is 0.  */
/* On the u'nSP all functions return their values in R1.  */
#define FUNCTION_VALUE(VALTYPE, FUNC) gen_rtx_REG (TYPE_MODE (VALTYPE), REG_R1)

/* Define how to find the value returned by a library function
   assuming the value has mode MODE.  */
#define LIBCALL_VALUE(MODE) gen_rtx_REG (MODE, REG_R1)

/* 1 if N is a possible register number for a function value. */
#define FUNCTION_VALUE_REGNO_P(N) ((N) == REG_R1)

/*
  How large values are returned
*/

/* A C expression which can inhibit the returning of certain function
   values in registers, based on the type of value.  A nonzero value
   says to return the function value in memory, just as large
   structures are always returned.  Here TYPE will be a C expression
   of type `tree', representing the data type of the value.

   Note that values of mode `BLKmode' must be explicitly handled by
   this macro.  Also, the option `-fpcc-struct-return' takes effect
   regardless of this macro.  On most systems, it is possible to
   leave the macro undefined; this causes a default definition to be
   used, whose value is the constant 1 for `BLKmode' values, and 0
   otherwise.

   Do not use this macro to indicate that structures and unions
   should always be returned in memory.  You should instead use
   `DEFAULT_PCC_STRUCT_RETURN' to indicate this.  */
#define RETURN_IN_MEMORY(TYPE) \
  ((TYPE_MODE (TYPE) == BLKmode) || int_size_in_bytes (TYPE) > 4)

/* Define this to be 1 if all structure return values must be in memory.
   If you define this macro to be 0, then the conventions used for
   structure and union return values are decided by the RETURN_IN_MEMORY
   macro.  */
#define DEFAULT_PCC_STRUCT_RETURN 1

/* If the structure value address is passed in a register, then
   `STRUCT_VALUE_REGNUM' should be the number of that register.  */
#define STRUCT_VALUE_REGNUM REG_R1

/* If the structure value address is not passed in a register, define
   `STRUCT_VALUE' as an expression returning an RTX for the place
   where the address is passed.  If it returns 0, the address is
   passed as an "invisible" first argument.  */
#define STRUCT_VALUE 0

/* If the incoming location is not a register, then you should define 
   STRUCT_VALUE_INCOMING as an expression for an RTX for where the 
   called function should find the value.  If it should find the value 
   on the stack, define this to create a MEM which refers to the frame 
   pointer.  A definition of 0 means that the address is passed as an 
   "invisible" first argument.  */
#define STRUCT_VALUE_INCOMING 0

/*
  Function entry and exit
*/

/* This macro generates the assembly code for function entry.
   FILE is a stdio stream to output the code to.
   SIZE is an int: how many units of temporary storage to allocate.
   Refer to the array `regs_ever_live' to determine which registers
   to save; `regs_ever_live[I]' is nonzero if register number I
   is ever used in the function.  This macro is responsible for
   knowing which registers should not be saved even if used. */

#define FUNCTION_PROLOGUE(FILE, SIZE) function_prologue (FILE, SIZE)
extern void function_prologue ();

/* EXIT_IGNORE_STACK should be nonzero if, when returning from a function,
   the stack pointer does not matter.  The value is tested only in
   functions that have frame pointers.
   No definition is equivalent to always zero.  */
#define EXIT_IGNORE_STACK 0

/* This macro generates the assembly code for function entry.
   FILE is a stdio stream to output the code to.
   SIZE is an int: how many units of temporary storage to allocate.
   Refer to the array `regs_ever_live' to determine which registers
   to save; `regs_ever_live[I]' is nonzero if register number I
   is ever used in the function.  This macro is responsible for
   knowing which registers should not be saved even if used. */
#define FUNCTION_EPILOGUE(FILE, SIZE) function_epilogue (FILE, SIZE)
extern void function_epilogue ();

/*
  Generating codes for profiling
*/

/* The u'nSP IDE provides a simulator */

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry. */
#define FUNCTION_PROFILER(FILE, LABELNO) \
  fprintf (FILE, "\t// got into FUNCTION_PROFILER with label #%d\n", LABELNO)

/* Output assembler code to FILE to initialize this source file's
   basic block profiling info, if that has not already been done.  */
#define FUNCTION_BLOCK_PROFILER(FILE, LABELNO)  \
  fprintf (FILE, "\t// got into FUNCTION_BLOCK_PROFILER with label #%d\n", \
	   LABELNO)

/* Output assembler code to FILE to increment the entry-count for
   the BLOCKNO'th basic block in this source file.  */
#define BLOCK_PROFILER(FILE, BLOCKNO) \
  fprintf (FILE, "\t// got into BLOCK_PROFILER with block #%d\n", BLOCKNO)

/*
  Implementing the varargs macros
*/

/* FIXME: it is empty now */

/*
  Trampolines for nested functions
*/

/* A C expression for the size in bytes of the trampoline, as an
   integer.  */
#define TRAMPOLINE_SIZE 4

/* Emit RTL insns to initialize the variable parts of a trampoline.
   FNADDR is an RTX for the address of the function's pure code.
   CHAIN is an RTX for the static chain value for the function.  */
/* We generate a two-instructions program at address TRAMP :
	R1 = CHAIN;
	PC = FNADDR;                                    */
#define INITIALIZE_TRAMPOLINE(TRAMP, FNADDR, CHAIN)                     \
{                                                                       \
  emit_move_insn (gen_rtx_MEM (QImode, TRAMP),                          \
		  GEN_INT(0x9309));                                     \
  emit_move_insn (gen_rtx_MEM (QImode, plus_constant (TRAMP, 1)),       \
		  CHAIN);                                               \
  emit_move_insn (gen_rtx_MEM (QImode, plus_constant (TRAMP, 6)),       \
		  GEN_INT(0x9F0F));                                     \
  emit_move_insn (gen_rtx_MEM (QImode, plus_constant (TRAMP, 8)),       \
		  FNADDR);                                              \
}

/*
  Implicit Calls to Library Routines
*/

/* Define this macro if GNU CC should generate calls to the System V 
   (and ANSI C) library functions memcpy and memset rather than the 
   BSD functions bcopy and bzero.  */
#define TARGET_MEM_FUNCTIONS

/*
  Addressing modes
*/

/* A C expression that is nonzero the machine supports
   post-increment addressing.  */
#define HAVE_POST_INCREMENT     1

/* Similar for other kinds of addressing.  */
#define HAVE_POST_DECREMENT     1
#define HAVE_PRE_INCREMENT      1
/*
#define HAVE_PRE_DECREMENT      0
*/

/* Recognize any constant value that is a valid address.  */
#define CONSTANT_ADDRESS_P(X)		  			\
  (GET_CODE (X) == LABEL_REF || GET_CODE (X) == SYMBOL_REF	\
   || GET_CODE (X) == CONST_INT || GET_CODE (X) == CONST || CONSTANT_P (X)) 
/*
#define CONSTANT_ADDRESS_P(X) \
  (CONSTANT_P (X) || GET_CODE (X) == SYMBOL_REF)
*/

/* Maximum number of registers that can appear in a valid memory address.  */
#define MAX_REGS_PER_ADDRESS    1

#ifdef REG_OK_STRICT

#define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P(REGNO (X))
#define REG_OK_FOR_INDEX_P(X) 0

/* A C compound statement with a conditional "goto LABEL;" executed
   if X (an RTX) is a legitimate memory address on the target machine
   for a memory operand of mode MODE.  */
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)                \
{                                                               \
  if (TARGET_DEBUG_UNSP_GCC)					\
    {								\
      fprintf (stderr, "In REG_OK_STRICT");  			\
      debug_rtx (X);                                            \
    }								\
  /* [r++], [r--], [++r] addressing modes */                    \
  if ((GET_CODE (X) == PRE_INC                                  \
       || GET_CODE (X) == POST_INC                              \
       || GET_CODE (X) == POST_DEC)                             \
      && REG_P (XEXP (X, 0))                                    \
      && REGNO (XEXP (X, 0)) < FIRST_PSEUDO_REGISTER)           \
    goto LABEL;                                                 \
								\
  /* Register Indirect addressing */                            \
  if (REG_P (X) && REGNO (X) < FIRST_PSEUDO_REGISTER)           \
    goto LABEL;                                                 \
								\
  /* Direct addressing */                                       \
  if (CONSTANT_ADDRESS_P (X))                                   \
    goto LABEL;                                                 \
								\
  /* u'nSP base register offset can only less than 64 */        \
  if (GET_CODE (X) == PLUS                                      \
      && GET_CODE (XEXP (X, 0)) == REG                          \
      && REG_OK_FOR_BASE_P (XEXP (X, 0))                        \
      && GET_CODE (XEXP (X, 1)) == CONST_INT                    \
      && INTVAL (XEXP (X, 1)) >= 0 				\
      && INTVAL (XEXP (X, 1)) <= (64 - GET_MODE_SIZE(MODE))) 	\
    goto LABEL;                                                 \
  if (TARGET_DEBUG_UNSP_GCC)					\
    fprintf (stderr, "is NOT a legitimate address\n\n");	\
}
/*
      && INTVAL (XEXP (X, 1)) >= 0                              \
      && INTVAL (XEXP (X, 1)) < 64)                             \
*/

#else /* not REG_OK_STRICT */

#define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P(REGNO (X))
#define REG_OK_FOR_INDEX_P(X) 0

/* A C compound statement with a conditional "goto LABEL;" executed
   if X (an RTX) is a legitimate memory address on the target machine
   for a memory operand of mode MODE.  */
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)                \
{                                                               \
  if (TARGET_DEBUG_UNSP_GCC)					\
    {								\
      fprintf (stderr, "In non REG_OK_STRICT\n"); 		\
      debug_rtx (X);                                            \
    }								\
  /* [r++], [r--], [++r] addressing modes */                    \
  if ((GET_CODE (X) == PRE_INC                                  \
       || GET_CODE (X) == POST_INC                              \
       || GET_CODE (X) == POST_DEC)                             \
      && REG_P (XEXP (X, 0)))                                   \
    goto LABEL;                                                 \
								\
  /* Register Indirect addressing */                            \
  if (REG_P (X))                                                \
    goto LABEL;                                                 \
								\
  /* Direct addressing */                                       \
  if (CONSTANT_ADDRESS_P (X))                                   \
    goto LABEL;                                                 \
								\
  /* u'nSP base register offset can only less than 64 */        \
  if (GET_CODE (X) == PLUS                                      \
      && GET_CODE (XEXP (X, 0)) == REG                          \
      && REG_OK_FOR_BASE_P (XEXP (X, 0))			\
      && GET_CODE (XEXP (X, 1)) == CONST_INT                    \
      && INTVAL (XEXP (X, 1)) >= 0 				\
      && INTVAL (XEXP (X, 1)) <= (64 - GET_MODE_SIZE(MODE)))	\
    goto LABEL;                                                 \
  if (TARGET_DEBUG_UNSP_GCC)					\
    fprintf (stderr, "illegitimate address\n\n"); 		\
}

#endif /* REG_OK_STRICT */

/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.
   This macro is used in only one place: `memory_address' in
   explow.c.
   OLDX is the address as it was before break_out_memory_refs
   was called.  In some cases it is useful to look at this to decide
   what needs to be done.  MODE and WIN are passed so that this macro
   can use GO_IF_LEGITIMATE_ADDRESS.
   It is always safe for this macro to do nothing.  It exists to
   recognize opportunities to optimize the output.  */
#define LEGITIMIZE_ADDRESS(X, OLDX, MODE, WIN)

/* A C statement or compound statement with a conditional `goto
   LABEL;' executed if memory address X (an RTX) can have different
   meanings depending on the machine mode of the memory reference it
   is used for.

   Autoincrement and autodecrement addresses typically have
   mode-dependent effects because the amount of the increment or
   decrement is the size of the operand being addressed.  Some
   machines have other mode-dependent addresses.  Many RISC machines
   have no mode-dependent addresses.

  You may assume that ADDR is a valid address for the machine.  */

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)	\
  if (GET_CODE (ADDR) == PRE_INC			\
      || GET_CODE (ADDR) == POST_DEC     		\
      || GET_CODE (ADDR) == POST_INC)			\
    goto LABEL
/*
#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR, LABEL)
*/

/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X saisifies CONSTANT_P or is a CONST_DOUBLE.  */
#define LEGITIMATE_CONSTANT_P(X) 1
/*
#define LEGITIMATE_CONSTANT_P(X) 		\
       ( GET_CODE(X) == CONST_INT  ?  1 :	\
         GET_CODE(X) == SYMBOL_REF ?  1 :	\
	 GET_CODE(X) == LABEL_REF  ?  1 :	\
	 GET_CODE(X) == CONST	   ?  1 : 	\
	 GET_CODE(X) == CONST_DOUBLE ?1 : 0 )
*/

/*
  Condition code status
*/

/* Store in cc_status the expressions
   that the condition codes will describe
   after execution of an instruction whose pattern is EXP.
   Do not alter them if the instruction would not alter the cc's.  */
#define NOTICE_UPDATE_CC(EXP, INSN) notice_update_cc (EXP)
extern void notice_update_cc ();

/*
  Describing relative costs of operations
*/

/* Compute the cost of computing a constant rtl expression RTX
   whose rtx-code is CODE.  The body of this macro is a portion
   of a switch statement.  If the code is computed here,
   return it with a return statement.  */
#define CONST_COSTS(RTX, CODE, OUTER_CODE)                      \
  case CONST_INT:                                               \
    if (GET_MODE (RTX) == QImode)                               \
      return (INTVAL (RTX) >= 0 && INTVAL (RTX) < 64) ? 1 : 2;  \
    else	                                      		\
      return 2;                                                 \
  case CONST:                                                   \
  case SYMBOL_REF:                                              \
  case LABEL_REF:                                               \
    return 2;                                                   \
  case CONST_DOUBLE:                                            \
    return 2;

/* This macro, if defined, is called for any case not handled by 
   the RTX_COSTS or CONST_COSTS macros.  This eliminates the need 
   to put case labels into the macro, but the code, or any functions 
   it calls, must assume that the RTL in x could be of any type that 
   has not already been handled.  The arguments are the same as for 
   RTX_COSTS, and the macro should execute a return statement giving 
   the cost of any RTL expressions that it can handle.  The default cost
   calculation is used for any RTL for which this macro does not 
   return a value.  */
#define DEFAULT_RTX_COSTS(X, CODE, OUTER_CODE)		\
  {							\
    int rtx_cost = unsp_rtx_cost (X, CODE, OUTER_CODE);	\
    if (rtx_cost != 0)					\
      return rtx_cost;					\
  }
extern int unsp_rtx_cost ();

/* An expression giving the cost of an addressing mode that
   contains ADDRESS.  If not defined, the cost is computed from the
   form of the ADDRESS expression and the `CONST_COSTS' values.

   For most CISC machines, the default cost is a good approximation
   of the true cost of the addressing mode.  However, on RISC
   machines, all instructions normally have the same length and
   execution time.  Hence all addresses will have equal costs.

   In cases where more than one form of an address is known, the
   form with the lowest cost will be used.  If multiple forms have
   the same, lowest, cost, the one that is the most complex will be
   used.

   For example, suppose an address that is equal to the sum of a
   register and a constant is used twice in the same basic block.
   When this macro is not defined, the address will be computed in
   a register and memory references will be indirect through that
   register.  On machines where the cost of the addressing mode
   containing the sum is no higher than that of a simple indirect
   reference, this will produce an additional instruction and
   possibly require an additional register.  Proper specification
   of this macro eliminates this overhead for such machines.

   Similar use of this macro is made in strength reduction of loops.

   ADDRESS need not be valid as an address.  In such a case, the
   cost is not relevant and can be any value; invalid addresses
   need not be assigned a different cost.

   On machines where an address involving more than one register is
   as cheap as an address computation involving only one register,
   defining `ADDRESS_COST' to reflect this can cause two registers
   to be live over a region of code where only one would have been
   if `ADDRESS_COST' were not defined in that manner.  This effect
   should be considered in the definition of this macro.
   Equivalent costs should probably only be given to addresses with
   different numbers of registers on machines with lots of registers.

   This macro will normally either not be defined or be defined as
   a constant.  */
/* #define ADDRESS_COST(ADDR) (CONSTANT_ADDRESS_P (ADDR) ? 9 : 7) */

/* A C expression for the cost of moving data from a register in
   class FROM to one in class TO.  The classes are expressed using
   the enumeration values such as `GENERAL_REGS'.  A value of 2 is
   the default; other values are interpreted relative to that.

   It is not required that the cost always equal 2 when FROM is the
   same as TO; on some machines it is expensive to move between
   registers if they are not general registers.

   If reload sees an insn consisting of a single `set' between two
   hard registers, and if `REGISTER_MOVE_COST' applied to their
   classes returns a value of 2, reload does not check to ensure
   that the constraints of the insn are met.  Setting a cost of
   other than 2 will allow reload to verify that the constraints are
   met.  You should do this if the `movM' pattern's constraints do
   not allow such copying.  */
/* #define REGISTER_MOVE_COST(FROM, TO) 3 */

/* A C expression for the cost of moving data of mode MODE between
   a register and memory. A value of 2 is the default.  */
/* #define MEMORY_MOVE_COST(MODE,CLASS,IN) \
  ((MODE == HImode || MODE == HFmode) ? 18 : 9) */

/* A C expression for the cost of a branch instruction.  A value of
   1 is the default; other values are interpreted relative to that.  */
/* #define BRANCH_COST 5 */

/* Define this macro as a C expression which is nonzero if accessing
   less than a word of memory (i.e. a `char' or a `short') is no
   faster than accessing a word of memory, i.e., if such access
   require more than one instruction or if there is no difference in
   cost between byte and (aligned) word loads.
   When this macro is not defined, the compiler will access a field by
   finding the smallest containing object; when it is defined, a
   fullword load will be used if alignment permits.  Unless bytes
   accesses are faster than word accesses, using word accesses is
   preferable since it may eliminate subsequent memory access if
   subsequent accesses occur to other fields in the same word of the
   structure, but to different bytes.  */
#define SLOW_BYTE_ACCESS 0

/* If a memory-to-memory move would take MOVE_RATIO or more simple
   move-instruction pairs, we will do a movstr or libcall instead.
   Increasing the value will always make code faster, but eventually
   incurs high cost in increased code size.
   If you don't define this, a reasonable default is used.  */
/* #define MOVE_RATIO 2  */

/* Define this macro if it is as good or better to call a constant
   function address than to call an address kept in a register.  */
#define NO_FUNCTION_CSE

/* Define this macro if it is as good or better for a function to
   call itself with an explicit address than to call an address
   kept in a register.  */
#define  NO_RECURSIVE_FUNCTION_CSE

/*
  Dividing the output into sections (texts, data, ...)
*/

#define TEXT_SECTION_ASM_OP ".code"
#define DATA_SECTION_ASM_OP ".iram"
/* The startup code does not clear all the RAM to zero,
   we have to make BSS section variables be put in IRAM.  */
#define BSS_SECTION_ASM_OP  ".iram"

/* Define this so gcc does not output a call to __main, since we
   are not currently supporting c++.  */
#define INIT_SECTION_ASM_OP 1

/* A list of names for sections other than the standard ones, which
   are 'in_text' and 'in_data' (and .bss if bss_section_asm_op is
   defined).  */
#define EXTRA_SECTIONS in_const

#define EXTRA_SECTION_FUNCTIONS                 \
extern void const_section ();                   \
						\
void                                            \
const_section(void)                             \
{                                               \
  if (in_section != in_const)                   \
    {                                           \
      fprintf (asm_out_file, ".text\n");        \
      in_section = in_const;                    \
    }                                           \
}

/* The name of the function that switches to the section to be used
   for read-only items.  */
#define READONLY_DATA_SECTION const_section

/* Define this marco to be an expression with a non-zero value
   if jump tables should be output in the text section ,along
   with the assembler instructions, Otherwise , the readonly data
   section is used.  */
#define JUMP_TABLES_IN_TEXT_SECTION 0

/*
  The overall framework of an assembler file
*/

/* Output at beginning of assembler file.  */
#define ASM_FILE_START(FILE) unsp_asm_file_start (FILE)
extern void unsp_asm_file_start ();

/* A C expression which outputs to the stdio stream FILE
   some appropriate text to go at the end of an assembler file.  */
#define ASM_FILE_END(FILE)   unsp_asm_file_end (FILE)
extern void unsp_asm_file_end ();

/* A C statement to output assembler commands which will identify
   the object file as having been compiled with GNU CC. If you
   don't define this macro, the string gcc_compiled.: is output.  */
#define ASM_IDENTIFY_GCC(FILE) fputs ("// gcc2_compiled.:\n\n", FILE)

/* A C string constant describing how to begin a comment in the
   target assembler language.  */
#define ASM_COMMENT_START "//"

/* A C string constant for text to be output before each asm statement
   or group of consecutive ones.  */
#define ASM_APP_ON "// GCC inline ASM start\n"

/* A C string constant for text to be output after each asm statement
   or group of consecutive ones.  */
#define ASM_APP_OFF "// GCC inline ASM end\n"

/* Like block addresses, stabs line numbers are relative to the
   current function.  */
#define ASM_OUTPUT_SOURCE_LINE(FILE, LINE)                      \
if (write_symbols == DBX_DEBUG)                                 \
  {                                                             \
    static int sym_lineno = 1;                                  \
    char buffer[256];                                           \
								\
    ASM_GENERATE_INTERNAL_LABEL (buffer, "LM", sym_lineno);     \
    fprintf (FILE, ".debug\n\t.dw \'");                         \
    fprintf (FILE, ".stabn 0x%x,0,%d,\',0,0\n", N_SLINE, LINE); \
    fprintf (FILE, "\t.dd ");                                   \
    assemble_name (FILE, buffer);                               \
    putc ('-', FILE);                                           \
    assemble_name (FILE, XSTR (XEXP (                           \
      DECL_RTL (current_function_decl), 0), 0));                \
    putc ('\n', FILE);                                          \
    fprintf (FILE, "\t.dw ");                                   \
    if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
      fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
    else							\
      fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
    force_data_section ();                                      \
    ASM_OUTPUT_INTERNAL_LABEL (FILE, "LM", sym_lineno);         \
    sym_lineno++;                                               \
  }

/* A C statement to output something to the assembler file to switch
   to section NAME for object DECL which is either a `FUNCTION_DECL',
   a `VAR_DECL' or `NULL_TREE'.  RELOC indicates whether the initial
   value of EXP requires link-time relocations.  The string given by
   NAME will always be the canonical version stored in the global
   stringpool.
   Some target formats do not support arbitrary sections.  Do not
   define this macro in such cases.
   At present this macro is only used to support section attributes.
   When this macro is undefined, section attributes are disabled.  */
#define ASM_OUTPUT_SECTION_NAME(STREAM, DECL, NAME, RELOC) \
  asm_output_section_name (STREAM, DECL, NAME, RELOC)
extern void asm_output_section_name();

/*
  Output of data
*/

/* DFmode */
#define ASM_OUTPUT_DOUBLE(FILE, VALUE)      asm_output_float (FILE, VALUE)
/* SFmode */
#define ASM_OUTPUT_FLOAT(FILE, VALUE)       asm_output_float (FILE, VALUE)
/* HFmode */
#define ASM_OUTPUT_SHORT_FLOAT(FILE, VALUE) asm_output_float (FILE, VALUE)
/* QFmode */
#define ASM_OUTPUT_BYTE_FLOAT(FILE, VALUE)  asm_output_float (FILE, VALUE)
extern void asm_output_float ();

/* Output UNITS_PER_WORD.
   GCC will repeatedly calling this macro once for each word.  */
#define ASM_OUTPUT_CHAR(FILE, VALUE)               \
{                                                  \
  fprintf (FILE, "\t.dw ");                        \
  if (GET_CODE (VALUE) == SYMBOL_REF               \
      && far_ptr_name (XSTR ((VALUE), 0)) == 1)    \
    fprintf (FILE, "%s_entry", XSTR ((VALUE), 0)); \
  else                                             \
    output_addr_const (FILE, (VALUE));             \
  fprintf (FILE, "\n");                            \
}

#define ASM_OUTPUT_BYTE(FILE, VALUE)    \
  fprintf ((FILE), "\t.dw %d\t// 0x%X\n", (int)(VALUE), (int)(VALUE))

#define ASM_OUTPUT_ASCII(FILE, PTR, LENGTH) asm_output_ascii(FILE, PTR, LENGTH)
extern void asm_output_ascii ();

/* Defined as C string constant, describing the syntax in the assembler
   for grouping arithmetic expressions.  */
#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"

/*
  Output of uninitialized variables
*/

/* This says how to output an assembler line to define a
   global common symbol.  */
#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED) \
  asm_output_common (FILE, NAME, SIZE, ROUNDED);
extern void asm_output_common ();

/* This says how to output an assembler line
   to define a local common symbol.  */
#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED)  \
  asm_output_local (FILE, NAME, SIZE, ROUNDED);
extern void asm_output_local ();

/*
  Output and generation of labels
*/

/* This is how to output the definition of a user-level label named NAME,
   such as the label on a static function or variable NAME.  */
#define ASM_OUTPUT_LABEL(FILE, NAME)  \
  do { assemble_name (FILE, NAME); fputs (":\n", FILE); } while (0)

/* A C statement (sans semicolon) to output to the stdio stream
    any text necessary for declaring the name of a function which is
    being defined.  */
#define ASM_DECLARE_FUNCTION_NAME(FILE, NAME, DECL)     \
 do {                                                   \
   assemble_name (FILE, NAME);                          \
   fputs (":\t.proc\n", FILE);                          \
 } while (0)

/* A C statement (sans semicolon) to output to the stdio stream
   any text necessary for declaring the size of a function which is
   being defined.  */
#define ASM_DECLARE_FUNCTION_SIZE(FILE, NAME, DECL) \
  do { fprintf(FILE, "\t.endp\t// end of %s\n\n", NAME); } while (0)

/* This is how to output a command to make the user-level label named NAME
   defined for reference from other files.  */

#define ASM_GLOBALIZE_LABEL(FILE, NAME)                 \
  do {                                                  \
    TREE_ASM_WRITTEN (get_identifier(NAME)) = 1;        \
    fputs (".public ", FILE);                           \
    assemble_name (FILE, NAME);                         \
    fputs ("\n", FILE);                                 \
  } while (0)

/* A C statement to output to the stdio stream any text necessary
   for declaring the name of an external symbol named name which
   is referenced in this compilation but not defined.  */
#define ASM_OUTPUT_EXTERNAL(FILE, DECL, NAME) \
  asm_output_external (NAME)
extern void asm_output_external ();

/* A C statement to output on stream an assembler pseudo-op to
   declare a library function named external.  */
#define ASM_OUTPUT_EXTERNAL_LIBCALL(FILE, FUN) \
  asm_output_external_libcall (FUN)
extern void output_external_libcall ();

/* This is how to output an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.  */
#define ASM_OUTPUT_INTERNAL_LABEL(FILE, PREFIX, NUM) \
  fprintf (FILE, "%s%d:\n", PREFIX, NUM)

/* This is how to store into the string LABEL
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.  */
#define ASM_GENERATE_INTERNAL_LABEL(LABEL, PREFIX, NUM) \
  sprintf (LABEL, "*%s%d", PREFIX, NUM)

/* Store in OUTPUT a string (made with alloca) containing
   an assembler-name for a local static variable or function
   named NAME. LABELNO is an integer which is different for
   each call.  */
#define ASM_FORMAT_PRIVATE_NAME(OUTPUT, NAME, LABELNO)        \
  do {                                                        \
    int len = strlen (NAME);                                  \
    char *temp = (char *) alloca (len + 3);                   \
    temp[0] = 'L';                                            \
    strcpy (&temp[1], (NAME));                                \
    temp[len + 1] = '_';                                      \
    temp[len + 2] = 0;                                        \
    (OUTPUT) = (char *) alloca (strlen (NAME) + 11);          \
    ASM_GENERATE_INTERNAL_LABEL (OUTPUT, temp, LABELNO);      \
  } while (0)

/*
  Output of assembler instructions
*/

#define REGISTER_NAMES  {"SP", "R1", "R2", "R3", "R4", "BP", "SOFT_BP", "SOFT_AP"}

#define PRINT_OPERAND(FILE, X, CODE) \
  unsp_print_operand (FILE, X, CODE)
extern void unsp_print_operand ();

/* Print a memory address as an operand to reference that memory location.  */
#define PRINT_OPERAND_ADDRESS(FILE, ADDR) \
  unsp_print_operand_address (FILE, ADDR)
extern void unsp_print_operand_address ();

/* The prefix to add to user-visible assembler symbols. */

#define REGISTER_PREFIX ""
#define LOCAL_LABEL_PREFIX ""
#define USER_LABEL_PREFIX "_"
#define IMMEDIATE_PREFIX ""

/* This is how to output an insn to push a register on the stack.
   It need not be very fast code since it is used only for profiling.  */
#define ASM_OUTPUT_REG_PUSH(FILE, REGNO) \
  fprintf (FILE, "\tpush %s to [sp]\n", reg_names[REGNO])

/* This is how to output an insn to pop a register from the stack.
   It need not be very fast code since it is used only for profiling.  */
#define ASM_OUTPUT_REG_POP(FILE, REGNO) \
  fprintf (FILE, "\tpop %s from [sp]\n", reg_names[REGNO])

/*
  Output of dispatch tables
*/

/* This macro should be provided on machines where the addresses in a dispatch
   table are relative to the table's own address. */
#define ASM_OUTPUT_ADDR_DIFF_ELT(FILE, BODY, VALUE, REL) \
  fprintf (FILE, "\t.dw L%d-L%d\n", VALUE, REL)

/* This is how to output an element of a case-vector that is absolute.
   Some targets don't use this, but we have to define it anyway.  */
/* This macro should be provided on machines where the addresses
   in a dispatch table are absolute.  */
#define ASM_OUTPUT_ADDR_VEC_ELT(FILE, VALUE) \
  fprintf (FILE, "\t.dw L%d\n", VALUE)

/*
  Assembler commands for alignment
*/

/* A C statement to output to the stdio stream FILE an assembler
   instruction to advance the location counter by SIZE bytes.  */
#define ASM_OUTPUT_SKIP(FILE, SIZE) \
  fprintf (FILE, "\t.dw %d dup(0)\n", (SIZE))

/* Define this marco if ASM_OUTPUT_SKIP should not be used int text
   section because it fails to put zero1 in the bytes that are skipped. */
#define ASM_NO_SKIP_IN_TEXT 1

/*This is how to output an assembler line that says to advance
  the location counter to a multiple of 2**LOG bytes.  We should
  not have to do any alignment since u'nsp is a word machine */
#define ASM_OUTPUT_ALIGN(FILE,LOG) fprintf(FILE,"")

/*
  Macros affecting all debugging formats
*/

/* A C expression that returns the DBX register number for the compiler
   register number REGNO.  In simple cases, the value of this expression
   may be REGNO itself.  */
#define DBX_REGISTER_NUMBER(REGNO)   (REGNO)

/* A C expression that returns the integer offset value for an automatic
   variable having address X (an RTL expression).  The default computation
   assumes that X is based on the frame-pointer and gives the offset from
   the frame-pointer.  */
#define DEBUGGER_AUTO_OFFSET(X) \
  (GET_CODE (X) == PLUS ? INTVAL (XEXP (X, 1)) : 0)

/* A C expression that returns the integer offset value for an argument
   having address X (an RTL expression).  */
#define DEBUGGER_ARG_OFFSET(OFFSET, X) \
  (OFFSET + 3)

#define PREFERRED_DEBUGGING_TYPE DBX_DEBUG

/*
  Specific options for DBX output
*/

#define DBX_DEBUGGING_INFO

/* Define this marco if all .stabs commands should be output
   while in the text section.  */
/* #define DEBUG_SYMS_TEXT */

#define ASM_STABS_OP ".debug\n\t.dw \'.stabs"
#define ASM_STABD_OP ".debug\n\t.dw \'.stabd"
#define ASM_STABN_OP ".debug\n\t.dw \'.stabn"

/* Inhibit splitting by defining this macro with the value zero.  */
/* #define DBX_CONTIN_LENGTH 0 */

/* Define this marco if the DBX information for a function and
   its args should precede the assembler code for the function.  */
#define DBX_FUNCTION_FIRST

/* Define this marco if the N_LBRAC symbol for a block should
   precede the debugging information for variables and functions
   defined in that block.  */
#define DBX_LBRAC_FIRST

/*
  Open-ended hooks for DBX format
*/

#define DBX_OUTPUT_LBRAC(FILE, NAME)                            \
{                                                               \
  fprintf (FILE, "%s 0x%x,0,0,\',0,0\n\t.dd ",                  \
	   ASM_STABN_OP, N_LBRAC);                              \
  assemble_name (FILE, NAME);                                   \
  putc ('-', FILE);                                             \
  assemble_name (FILE, XSTR (XEXP (                             \
		 DECL_RTL (current_function_decl), 0), 0));     \
  putc ('\n', FILE);                                            \
  fprintf (FILE, "\t.dw ");                                     \
  if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
    fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
  else							\
    fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
  force_data_section ();                                        \
}

#define DBX_OUTPUT_RBRAC(FILE, NAME)                            \
{                                                               \
  fprintf (FILE, "%s 0x%x,0,0,\',0,0\n\t.dd ",                  \
	   ASM_STABN_OP, N_RBRAC);                              \
  assemble_name (FILE, NAME);                                   \
  putc ('-', FILE);                                             \
  assemble_name (FILE,XSTR (XEXP (                              \
		 DECL_RTL (current_function_decl), 0), 0));     \
  putc ('\n', FILE);                                            \
  fprintf (FILE, "\t.dw ");                                     \
  if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
    fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
  else							\
    fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
  force_data_section ();                                        \
}

#define DBX_OUTPUT_FUNCTION_END(FILE, FUNC) \
  unsp_dbx_output_function_end (FILE, FUNC)
extern void unsp_dbx_output_function_end ();

/*
  File names in DBX format
*/

#define DBX_WORKING_DIRECTORY 1

#ifdef __CYGWIN__

#define DBX_OUTPUT_MAIN_SOURCE_FILENAME(FILE, NAME)             \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext", 0);   \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  cygwin32_conv_to_full_win32_path (NAME, unsp_tmpstr);         \
  fprintf (FILE, "\"%s\"", unsp_tmpstr);                        \
  fprintf (FILE, ",0x%x,0,3,\',0,0,offset %s,seg %s,",          \
    N_SO, &ltext_label_name[1], &ltext_label_name[1]);          \
  if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
    fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
  else							\
    fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", 0);                 \
}

#define DBX_OUTPUT_MAIN_SOURCE_DIRECTORY(FILE, NAME)            \
{                                                               \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  cygwin32_conv_to_full_win32_path (NAME, unsp_tmpstr);         \
  fprintf (FILE, "\"%s\"", unsp_tmpstr);                        \
  fprintf (FILE, ",0x%x,0,3,\',0,0,offset %s,seg %s,",          \
     N_SO, &ltext_label_name[1],&ltext_label_name[1]);          \
  if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
    fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
  else							\
    fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
  force_data_section ();                                        \
}

#define DBX_OUTPUT_SOURCE_FILENAME(FILE, NAME)                  \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext",       \
             source_label_number);                              \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  cygwin32_conv_to_full_win32_path (NAME, unsp_tmpstr);         \
  fprintf (FILE, "\"%s\"", unsp_tmpstr);                        \
  fprintf (FILE, ",0x%x,0,0,\',0,0,offset %s, seg %s,",         \
    N_SOL, &ltext_label_name[1], &ltext_label_name[1]);         \
  if (current_function_decl && UNSP_ISR_FLAG (current_function_decl)) \
    fprintf (FILE, "0x0d,0x0a\n.text\n");                     \
  else							\
    fprintf (FILE, "0x0d,0x0a\n.code\n");                       \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", source_label_number); \
  source_label_number++;                                        \
}

#else

#define DBX_OUTPUT_MAIN_SOURCE_FILENAME(FILE, NAME)             \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext", 0);   \
  fprintf (FILE, ".stabs ");                                    \
  output_quoted_string (FILE, NAME);                            \
  fprintf (FILE, ", 0x%x, 0, 3, %s\n",                          \
           N_SO, &ltext_label_name[1]);                         \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", 0);                 \
}

#define DBX_OUTPUT_MAIN_SOURCE_DIRECTORY(FILE, NAME)            \
{                                                               \
  fprintf (FILE, ".stabs ");                                    \
  output_quoted_string (FILE, NAME);                            \
  fprintf (FILE, ", 0x%x, 0, 3, %s\n",                          \
     N_SO, &ltext_label_name[1]);                               \
  force_data_section ();                                        \
}

#define DBX_OUTPUT_SOURCE_FILENAME(FILE, NAME)                  \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext",       \
             source_label_number);                              \
  fprintf (FILE, ".stabs ");                                    \
  output_quoted_string (FILE, NAME);                            \
  fprintf (FILE, ", 0x%x, 0, 0, %s\n",                          \
    N_SOL, &ltext_label_name[1]);                               \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", source_label_number); \
  source_label_number++;                                        \
}

#if 0
/* 2002/05/08:
   Change to use .stabs format to fix bug.
   When filename or path contains single apostrophe, it will
   confuse the assembler.  */
#define DBX_OUTPUT_MAIN_SOURCE_FILENAME(FILE, NAME)             \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext", 0);   \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  output_quoted_string (FILE, NAME);				\
  fprintf (FILE, ",0x%x,0,3,\',0,0,offset %s,seg %s,",          \
    N_SO, &ltext_label_name[1], &ltext_label_name[1]);          \
  fprintf (FILE, "0x0d,0x0a\n.code\n");                         \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", 0);                 \
}

#define DBX_OUTPUT_MAIN_SOURCE_DIRECTORY(FILE, NAME)            \
{                                                               \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  output_quoted_string (FILE, NAME);                            \
  fprintf (FILE, ",0x%x,0,3,\',0,0,offset %s,seg %s,",          \
     N_SO, &ltext_label_name[1],&ltext_label_name[1]);          \
  fprintf (FILE, "0x0d,0x0a\n.code\n");                         \
  force_data_section ();                                        \
}

#define DBX_OUTPUT_SOURCE_FILENAME(FILE, NAME)                  \
{                                                               \
  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext",       \
             source_label_number);                              \
  fprintf (FILE, "%s ", ASM_STABS_OP);                          \
  output_quoted_string (FILE, NAME);                            \
  fprintf (FILE, ",0x%x,0,0,\',0,0,offset %s, seg %s,",         \
    N_SOL, &ltext_label_name[1], &ltext_label_name[1]);         \
  fprintf (FILE, "0x0d,0x0a\n.code\n");                         \
  text_section ();                                              \
  ASM_OUTPUT_INTERNAL_LABEL (FILE, "Ltext", source_label_number); \
  source_label_number++;                                        \
}
#endif

#endif

/*
  Cross compilation and floating point
*/

/* Define if you don't want extended real, but do want to use the
   software floating point emulator for REAL_ARITHMETIC and
   decimal <-> binary conversion.  */
#define REAL_ARITHMETIC

/*
  Miscellaneous parameters
*/

/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.  */
#define CASE_VECTOR_MODE QImode

/* Define if operations between registers always perform the operation
   on the full register even if a narrower mode is specified.  */
#define WORD_REGISTER_OPERATIONS

/* Specify the tree operation to be used to convert reals
   to integers.  */
#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR

/* This is the kind of divide that is easiest to do in the general case.  */
#define EASY_DIV_EXPR TRUNC_DIV_EXPR

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX 1

/* Value is 1 if truncating an integer of INPREC bits to OUTPREC bits
   is done just by pretending it is already truncated.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* An alias for the machine mode used for pointers */
#define Pmode QImode

/* An alias for the machine mode used for memory references to functions
   being called, in call RTL expression.  */
#define FUNCTION_MODE QImode

/* If defined, a C expression whose value is nonzero if IDENTIFIER
   with arguments ARGS is a valid machine specific attribute for DECL.
   The attributes in ATTRIBUTES have previously been assigned to DECL.  */
/*
#define VALID_MACHINE_DECL_ATTRIBUTE(DECL, ATTRIBUTES, NAME, ARGS) \
  (unsp_valid_decl_attribute_p (DECL, ATTRIBUTES, NAME, ARGS))
extern int unsp_valid_decl_attribute_p ();

#define VALID_MACHINE_TYPE_ATTRIBUTE(TYPE, ATTRIBUTES, NAME, ARGS) \
  (unsp_valid_type_attribute_p (TYPE, ATTRIBUTES, NAME, ARGS))
extern int unsp_valid_type_attribute_p ();
*/

#define DOLLARS_IN_IDENTIFIERS 0
#define NO_DOLLAR_IN_LABEL
#define NO_DOT_IN_LABEL
