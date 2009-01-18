#include "regdef.h"

/*
**
** LEXRA 4080 support library
**
** Developer: 
** potatooo, sunplus midnight workshop.
**
** Note:
** all right reserved.
**
*/

#if	defined(__MIPSEB__)||defined(__MIPSEB)
#define	LIBGCC1_BIG_ENDIAN
#define	out_H	v0
#define	out_L	v1
#define	in0_H	a0
#define	in0_L	a1
#define	in1_H	a2
#define	in1_L	a3
#elif 	defined(__MIPSEL__)||defined(__MIPSEL)
#define	out_H	v1
#define	out_L	v0
#define	in0_H	a1
#define	in0_L	a0
#define	in1_H	a3
#define	in1_L	a2
#else
#err	"must specify MIPS endian!"
#endif


/*
** FUNCTION
**  (U)INT32 v0 = __mulsi3((U)INT32 a0, (U)INT32 a1);
** REGISTERS:
**	use		t0
**	modify		a0
**			a1	-> become 0
** NOTE:
** 	this seems to give better performance to just rotate and add.
**
*/
#ifdef	L_Xmulsi3
		.text
		.global	__Xumulsi3
		.global	__Xmulsi3
/************** signed multiplication (32x32) ***************************/
		.ent	__Xmulsi3
__Xumulsi3:
__Xmulsi3:
		move	v0, zero
__Xmulsi3_loop:
		andi	t0, a1, 1		/* t0 = multiplier[0]	*/
		srl	a1, 1			/* a1 /= 2		*/
		beqz	t0, __Xmulsi3_loop2	/* skip if (t0==0)	*/
		addu	v0, a0			/* add multiplicand	*/
__Xmulsi3_loop2:
		sll	a0, 1			/* multiplicand mul 2	*/
		bnez	a1, __Xmulsi3_loop
		jr	ra
		.end	__Xmulsi3
#endif/*L_Xmulsi3*/


/*
** FUNCTION
**  UINT64 (v0,v1) = __Xumulsidi3(UINT32 a0, UINT32 a1);
**   INT64 (v0,v1) =  __Xmulsidi3( INT32 a0,  INT32 a1);
** REGISTERS:
**	uses		t0, t1
**	modifies	a0	-> clobbered
**			a1	-> become 0
** NOTE:
**	1. signed multiplication is implemented thru. inverted sign
**	2. this is not used in (2.8.1/1.1.1/1.1.2) implementaions
**
*/
#ifdef	L_Xmulsidi3
		.text
		.global	__Xumulsidi3
		.global	__Xmulsidi3

/************** unsigned multiplication (32x32 to 64) *******************/
		.ent	__Xumulsidi3
__Xumulsidi3:
		move	t1, zero		/* (t1): high-part of	*/
						/*   the multiplicand	*/
__Xumulsidi3_entry:
		move	out_H, zero		/* clear result		*/
		move	out_L, zero		
__Xumulsidi3_loop:
		andi	t0, a1, 1		/* t0 = multipier [0]	*/
                srl	a1, 1			/* multiplier /= 2	*/
		beqz	t0, __Xumulsidi3_loop2
		addu	out_L, a0		/* add multiplicand 	*/
		sltu	t0, out_L, a0		/* save carry in t0	*/
		addu	out_H, t1		/* add high to high	*/
		addu	out_H, t0		/* add carry to high	*/
__Xumulsidi3_loop2:
		srl	t0, a0, 31		/* multiplicand mul 2	*/
		sll	a0, a0, 1
		sll	t1, t1, 1
		or	t1, t1, t0
		bnez	a1, __Xumulsidi3_loop
		jr	ra
		.end	__Xumulsidi3

/************** signed multiplication (32x32 to 64) *********************/
		.ent	__Xmulsidi3
__Xmulsidi3:
		bgez	a1, __Xmulsidi3_a1p	/* chk multiplier sign	*/
		negu	a0
		negu	a1
__Xmulsidi3_a1p:
		srl	t1, a0, 31		/* sign-ext a0 to (t1)	*/
		b	__Xumulsidi3_entry	/* borrow umulsidi3	*/
		.end	__Xmulsidi3	
#endif/*L_mulsidi3*/


/*
** FUNCTION
**  UINT64 (v1,v0) = __Xumuldi3(UINT64 (a1,a0), UINT64 (a3,a2));
**   INT64 (v1,v0) =  __Xmuldi3( INT64 (a1,a0),  INT64 (a3,a2));
** DESCRIPTION:
** 	performs 64x64 -> 64 multiplication.
** REGISTERS:
**	used		t0, t1
**	modified	a0, a1, a2, a3
**
*/
#ifdef	L_Xmuldi3
		.text	
		.global	__Xumuldi3
		.global	__Xmuldi3

/************** signed multiplication (64x64) ***************************/
		.ent	__Xmuldi3
__Xumuldi3:
__Xmuldi3:
		move	out_H, zero		/* clear result		*/
		move	out_L, zero
__Xmuldi3_loop:
		andi	t0, in1_L, 1		/* t0 = multiplier[0]	*/
		sll	t1, in1_H, 31		/* multiplier div 2	*/
		srl	in1_H, 1
                srl	in1_L, 1
 		or	in1_L, t1
		beqz	t0, __Xmuldi3_loop2
		addu	out_L, out_L, in0_L	/* add multiplicand	*/
		sltu	t0, out_L, in0_L	/* save carry in t0	*/
		addu	out_H, out_H, in0_H	/* add high-part (a1)	*/
		addu	out_H, t0		/* add carry 		*/
__Xmuldi3_loop2:
		or	t1, in1_H, in1_L	/* check (multipler=0)	*/
		srl	t0, in0_L, 31		/* multiplicand mul 2	*/
		sll	in0_H, 1		
		sll	in0_L, 1		
		or	in0_H, in0_H, t0
		bnez	t1, __Xmuldi3_loop
		jr	ra
		.end	__Xmuldi3
#endif/*L_Xmuldi3*/


/*
** FUNCTION
** UINT32(v0) = __Xudivsi3(UINT32 (a0), UINT32 (a1));
**  INT32(v0) =  __Xdivsi3( INT32 (a0),  INT32 (a1));
** UINT32(v0) = __Xumodsi3(UINT32 (a0), UINT32 (a1));
**  INT32(v0) =  __Xmodsi3( INT32 (a0),  INT32 (a1));
** DESCRIPTION
**	performs 32-bit division/modulo.
** REGISTERS
**	used	t0	bit-index
**		t1	
**	modify	a0 	becomes remainer
**
*/
#ifdef	L_Xdivsi3
		.text
		.global	__Xudivsi3
		.global	__Xumodsi3
		.global	__Xdivsi3
		.global	__Xmodsi3

/************** unsigned division ***************************************/
		.ent	__Xudivsi3
__Xudivsi3:		
		move	v0, zero
		beqz	a1, __Xuds_exit		/* check (divisor==0)	*/
		li	t0, 1			/* set bit-idx t0=0 	*/
		bltz	a1, __Xuds_ok		/* check a1 MSB		*/
__Xuds_normalize:
		sltu	t1, a0, a1		/* a0<a1 ?		*/
		bnez	t1, __Xuds_ok	
		sll	a1, 1			/* shift divisor <<	*/
		sll	t0, 1			/* shift bit-idx <<	*/
		bgez	a1, __Xuds_normalize	/* avoid a1 MSB OvF	*/
__Xuds_ok:
__Xuds_loop2:
		sltu	t1, a0, a1		/* t1=1 if (a0<a1)	*/
		bnez	t1, __Xuds_loop3
		subu	a0, a1			/* - divisor<<bit-idx	*/
		or	v0, v0, t0		/* make qoutient	*/
__Xuds_loop3:
		srl	t0, t0, 1		/* shift bit-idx >>	*/
		srl	a1, a1, 1		/* shift divisor >>	*/
		bnez	t0, __Xuds_loop2	/* check bit-idx 	*/
__Xuds_exit:	
		jr	ra
		.end	__Xudivsi3

/************** unsigned modulus ****************************************/
		.ent	__Xumodsi3
__Xumodsi3:
		move	t3, ra			/* save ra in t3	*/
		jal	__Xudivsi3		/* borrow udivsi3 code	*/
		move	v0, a0			/* get remainder (a0)	*/
		jr	t3			/* jump t3 (saved-ra)	*/
		.end	__Xumodsi3

/************** abs and div *********************************************/
		.ent	__Xorgsi3
__Xorgsi3:
		bgez	a0, __Xorgsi3_a0p	/* rip sign of dividend	*/
		negu	a0
__Xorgsi3_a0p:
		bgez	a1, __Xudivsi3		/* goto udivsi3		*/
		negu	a1
		b	__Xudivsi3		/* goto udivsi3		*/
		.end	__Xorgsi3

/************** signed division *****************************************/
		.ent	__Xdivsi3
__Xdivsi3:		
		move	t3, ra			/* save ra in t3	*/
		xor	t2, a0, a1		/* t2[31]=sgn(quotient) */
		jal	__Xorgsi3
__Xdivsi3_adjust:
		bgez	t2, __Xdivsi3_exit
		negu	v0			/* adj sign(quotient)	*/
__Xdivsi3_exit:	
		jr	t3			/* jump to t3(ra)	*/
		.end	__Xdivsi3

/************** signed modulus ******************************************/
		.ent	__Xmodsi3
__Xmodsi3:
		move	t3, ra			/* save ra in t3	*/
		move	t2, a0			/* save sign in t2 MSB	*/
		jal	__Xorgsi3		/* go to absdiv		*/
		move	v0, a0			/* retrieve result	*/
		b	__Xdivsi3_adjust
		.end	__Xmodsi3
#endif/*L_Xdivsi3*/


/*
** FUNCTION
** UINT64(v0,v1) = __Xudivdi3(UINT64 (a0,a1), UINT64 (a2,a3));
**  INT64(v0,v1) =  __Xdivdi3( INT64 (a0,a1),  INT64 (a2,a3));
** UINT64(v0,v1) = __Xumoddi3(UINT64 (a0,a1), UINT64 (a2,a3));
**  INT64(v0,v1) =  __Xmoddi3( INT64 (a0,a1),  INT64 (a2,a3));
** DESCRIPTION
**	perform long-long div/mod operations
** REGISTERS:
**	used	t0
**		[t2,t1]	64-bit bit-index
**		[t4,t3]	64-bit bit-mask
**	modify	a0,a1 	becomes remainer
** NOTE:
**	divided by zero you get garbage
**
*/
#ifdef	L_Xdivdi3
		.text
		.global	__Xudivdi3
		.global	__Xumoddi3
		.global	__Xdivdi3
		.global	__Xmoddi3
/************** unsigned division (64/64->64) ***************************/
		.ent	__Xudivdi3
__Xudivdi3:		
		or	t0, in1_H, in1_L 
		move	out_H, zero		/* clear result		*/
		move	out_L, zero		
		beqz	t0, __Xudivdi3_exit	/* check (divisor==0)	*/
		lui	t4, 0x8000		/* set (t4:t3)[63]=1	*/
		move	t3, zero
		move	t2, zero		/* set (t2:t1) bit-idx	*/
		li	t1, 1			
__Xudivdi3_count_leading_zeros:
		and	out_L, in0_H, t4	/* check in1 by t4:t3	*/
		and	t0, in0_L, t3		
		or	t0, out_L
		sll	out_L, t4, 31		/* shift bit-msk >> (D)	*/
		bnez	t0, __Xudivdi3_normalize
		sra	t4, 1			
		srl	t3, 1
		or	t3, out_L		/* comes from above 	*/
		b	__Xudivdi3_count_leading_zeros
__Xudivdi3_normalize:
		and	out_L, in1_H, t4	/* check in1 by t4:t3	*/
		and	t0, in1_L, t3
		or	t0, out_L
		srl	out_L, t1, 31		/* shift bit-idx <<	*/
		bnez	t0, __Xudivdi3_ok
		sll	t1, 1			/* shft-lo		*/
		sll	t2, 1			/* shft-hi		*/
		or	t2, out_L			
		srl	out_L, in1_L, 31	/* shift divisor <<	*/
		sll	in1_L, 1		/* shft-lo		*/
		sll	in1_H, 1		/* shft-hi		*/
		or	in1_H, out_L
		b	__Xudivdi3_normalize
__Xudivdi3_ok:
		move	out_L, zero
__Xudivdi3_try_subtract:
		sltu	t0, in0_H, in1_H	/* test hi-part (h-c)	*/
		sll	t4, t2, 31		/* sht bit-idx >> (t4)	*/
		bnez	t0, __Xudivdi3_less	/* high-less		*/
		sltu	t3, in0_L, in1_L	/* test low-part (l-c)	*/
		bne	in0_H, in1_H, __Xudivdi3_bigger
		bnez	t3, __Xudivdi3_less	/* high-equ -> low-less	*/
__Xudivdi3_bigger: 
		subu	in0_H, in1_H		/* update remainder	*/
		subu	in0_H, t3		/* carry 		*/
		subu	in0_L, in1_L
		or	out_L, t1		/* make qoutient	*/
		or	out_H, t2		
__Xudivdi3_less:
		srl	t1, 1			/* sht bit-idx >>	*/
		srl	t2, 1
		or	t1, t4			
		or	t3, t2, t1		/* chk bit-idx 		*/
		sll	t0, in1_H, 31		/* shift divisor >>	*/
		srl	in1_L, 1
		srl	in1_H, 1
		or	in1_L, t0
		bnez	t3, __Xudivdi3_try_subtract
__Xudivdi3_exit:	
		jr	ra
		.end	__Xudivdi3

/************** unsigned modulus (64/64->64) ****************************/
		.ent	__Xumoddi3
__Xumoddi3:	
		move	t7, ra			/* save return address	*/
		jal	__Xudivdi3		/* borrow from udivdi3	*/
		move	out_L, in0_L		/* adjust result	*/
		move	out_H, in0_H		
		jr	t7
		.end	__Xmoddi3

/************** get absolute value of in0 and in1 and borrow udiv64 ****/
		.ent	__Xorgdi
__Xorgdi:
		bgez	in0_H, __Xorgdi_i0p	/* check in0 sign	*/
		negu	in0_L, in0_L	
		sltu	t0, zero, in0_L		/* t2=1 if (0<in0_L)	*/
		negu	in0_H, in0_H
		subu	in0_H, t0
__Xorgdi_i0p:
		bgez	in1_H, __Xudivdi3	/* check in1 sign	*/
		negu	in1_L, in1_L
		sltu	t0, zero, in1_L		/* save carry		*/
		negu	in1_H, in1_H
		subu	in1_H, t0
		b	__Xudivdi3		/* borrow from udivdi3	*/
		.end	__Xorgdi

/************** signed division (64/64->64) *****************************/
		.ent	__Xdivdi3
__Xdivdi3:
		move	t7, ra			/* save return address	*/
		xor	t6, in0_H, in1_H	/* sgn(in0*in1) in t6	*/
		jal	__Xorgdi
__Xdivdi3_adjust:
		bgez	t6, __Xdivdi3_pos	/* check if neg 	*/
		negu	out_L, out_L
		negu	out_H, out_H
		sltu	t0, zero, out_L		/* check carry		*/
		subu	out_H, t0
__Xdivdi3_pos:
		jr	t7			/* return (ra)		*/
		.end	__Xdivdi3

/************** signed modulus (64/64->64) ******************************/
		.ent	__Xmoddi3
__Xmoddi3:	
		move	t7, ra			/* save return address	*/
		move	t6, in0_H		/* sgn(in0) in t6 MSB	*/
		jal	__Xorgdi
		move	out_L, in0_L
		move	out_H, in0_H
		b	__Xdivdi3_adjust	/* goto adjust result	*/
		.end	__Xmoddi3
#endif/*L_Xdivdi3*/


/*
** FUNCTION
** __Xfabsf, __Xfabsd
**
** DESCRIPTION
**	get absolute value of a float(double) argument with no checking
**	for NaNs.
** NOTE
**	1. currently there is no operation will mapped to SF mode abs.
**
*/
#ifdef	L_Xfabs
		.text
		.global	__Xfabsf
		.global	__Xfabsd
		.ent	__Xfabsf
__Xfabsf:
		sll	v0, a0, 1
		srl	v0, 1
		j	ra
		.end	__Xfabsf
		.ent	__Xfabsd
__Xfabsd:
		move	out_L, in0_L
		sll	out_H, in0_H
		srl	out_H, 1
		j	ra
		.end	__Xfabsd
#endif/*L_Xfabs*/
/* mips16 floating point support code
   Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.
   Contributed by Cygnus Support

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2, or (at your option) any
later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file with other programs, and to distribute
those programs without any restriction coming from the use of this
file.  (The General Public License restrictions do apply in other
respects; for example, they cover modification of the file, and
distribution when not linked into another program.)

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

/* This file contains mips16 floating point support functions.  These
   functions are called by mips16 code to handle floating point when
   -msoft-float is not used.  They accept the arguments and return
   values using the soft-float calling convention, but do the actual
   operation using the hard floating point instructions.  */

/* This file contains 32 bit assembly code.  */
	.set nomips16

/* Start a function. */

#define STARTFN(NAME) .globl NAME; .ent NAME; NAME:

/* Finish a function.  */

#define ENDFN(NAME) .end NAME

/* Single precision math.  */

/* This macro defines a function which loads two single precision
   values, performs an operation, and returns the single precision
   result.  */

#define SFOP(NAME, OPCODE)	\
STARTFN (NAME);			\
	.set	noreorder;	\
	mtc1	$4,$f0;		\
	mtc1	$5,$f2;		\
	nop;			\
	OPCODE	$f0,$f0,$f2;	\
	mfc1	$2,$f0;		\
	j	$31;		\
	nop;			\
	.set	reorder;	\
	ENDFN (NAME)

#ifdef L_m16addsf3
SFOP(__mips16_addsf3, add.s)
#endif
#ifdef L_m16subsf3
SFOP(__mips16_subsf3, sub.s)
#endif
#ifdef L_m16mulsf3
SFOP(__mips16_mulsf3, mul.s)
#endif
#ifdef L_m16divsf3
SFOP(__mips16_divsf3, div.s)
#endif

#define SFOP2(NAME, OPCODE)	\
STARTFN (NAME);			\
	.set	noreorder;	\
	mtc1	$4,$f0;		\
	nop;			\
	OPCODE	$f0,$f0;	\
	mfc1	$2,$f0;		\
	j	$31;		\
	nop;			\
	.set	reorder;	\
	ENDFN (NAME)
	
#ifdef L_m16negsf2
SFOP2(__mips16_negsf2, neg.s)
#endif
#ifdef L_m16abssf2
SFOP2(__mips16_abssf2, abs.s)
#endif
	
/* Single precision comparisons.  */

/* This macro defines a function which loads two single precision
   values, performs a floating point comparison, and returns the
   specified values according to whether the comparison is true or
   false.  */

#define SFCMP(NAME, OPCODE, TRUE, FALSE)	\
STARTFN (NAME);					\
	mtc1	$4,$f0;				\
	mtc1	$5,$f2;				\
	OPCODE	$f0,$f2;			\
	li	$2,TRUE;			\
	bc1t	1f;				\
	li	$2,FALSE;			\
1:;						\
	j	$31;				\
	ENDFN (NAME)

/* This macro is like SFCMP, but it reverses the comparison.  */

#define SFREVCMP(NAME, OPCODE, TRUE, FALSE)	\
STARTFN (NAME);					\
	mtc1	$4,$f0;				\
	mtc1	$5,$f2;				\
	OPCODE	$f2,$f0;			\
	li	$2,TRUE;			\
	bc1t	1f;				\
	li	$2,FALSE;			\
1:;						\
	j	$31;				\
	ENDFN (NAME)

#ifdef L_m16eqsf2
SFCMP(__mips16_eqsf2, c.eq.s, 0, 1)
#endif
#ifdef L_m16nesf2
SFCMP(__mips16_nesf2, c.eq.s, 0, 1)
#endif
#ifdef L_m16gtsf2
SFREVCMP(__mips16_gtsf2, c.lt.s, 1, 0)
#endif
#ifdef L_m16gesf2
SFREVCMP(__mips16_gesf2, c.le.s, 0, -1)
#endif
#ifdef L_m16lesf2
SFCMP(__mips16_lesf2, c.le.s, 0, 1)
#endif
#ifdef L_m16ltsf2
SFCMP(__mips16_ltsf2, c.lt.s, -1, 0)
#endif

/* Single precision conversions.  */

#ifdef L_m16fltsisf
STARTFN (__mips16_floatsisf)
	.set	noreorder
	mtc1	$4,$f0
	nop
	cvt.s.w	$f0,$f0
	mfc1	$2,$f0
	j	$31
	nop
	.set	reorder
	ENDFN (__mips16_floatsisf)
#endif

#ifdef L_m16fixsfsi
STARTFN (__mips16_fixsfsi)
	.set	noreorder
	mtc1	$4,$f0
	nop
	trunc.w.s $f0,$f0,$4
	mfc1	$2,$f0
	j	$31
	nop	
	.set	reorder
	ENDFN (__mips16_fixsfsi)
#endif

#if !defined(__mips_single_float) && !defined(__SINGLE_FLOAT)
		
/* The double precision operations.  We need to use different code
   based on the preprocessor symbol __mips64, because the way in which
   double precision values will change.  Without __mips64, the value
   is passed in two 32 bit registers.  With __mips64, the value is
   passed in a single 64 bit register.  */

/* Load the first double precision operand.  */

#if defined(__mips64)
#define LDDBL1 dmtc1 $4,$f12
#elif defined(__mipsfp64)
#define LDDBL1 sw $4,0($29); sw $5,4($29); l.d $f12,0($29)
#elif defined(__MIPSEB__)	
#define LDDBL1 mtc1 $4,$f13; mtc1 $5,$f12
#else	
#define LDDBL1 mtc1 $4,$f12; mtc1 $5,$f13
#endif

/* Load the second double precision operand.  */

#if defined(__mips64)
/* XXX this should be $6 for Algo arg passing model */
#define LDDBL2 dmtc1 $5,$f14
#elif defined(__mipsfp64)
#define LDDBL2 sw $6,8($29); sw $7,12($29); l.d $f14,8($29)
#elif defined(__MIPSEB__)	
#define LDDBL2 mtc1 $6,$f15; mtc1 $7,$f14
#else	
#define LDDBL2 mtc1 $6,$f14; mtc1 $7,$f15
#endif
	
/* Move the double precision return value to the right place.  */

#if defined(__mips64)
#define RETDBL dmfc1 $2,$f0
#elif defined(__mipsfp64)
#define RETDBL s.d $f0,0($29); lw $2,0($29); lw $3,4($29)
#elif defined(__MIPSEB__)	
#define RETDBL mfc1 $2,$f1; mfc1 $3,$f0
#else	
#define RETDBL mfc1 $2,$f0; mfc1 $3,$f1
#endif
	
/* Double precision math.  */

/* This macro defines a function which loads two double precision
   values, performs an operation, and returns the double precision
   result.  */

#define DFOP(NAME, OPCODE)	\
STARTFN (NAME);			\
	.set	noreorder;	\
	LDDBL1;			\
	LDDBL2;			\
	nop;			\
	OPCODE	$f0,$f12,$f14;	\
	RETDBL;			\
	j	$31;		\
	nop;			\
	.set	reorder;	\
	ENDFN (NAME)

#ifdef L_m16adddf3
DFOP(__mips16_adddf3, add.d)
#endif
#ifdef L_m16subdf3
DFOP(__mips16_subdf3, sub.d)
#endif
#ifdef L_m16muldf3
DFOP(__mips16_muldf3, mul.d)
#endif
#ifdef L_m16divdf3
DFOP(__mips16_divdf3, div.d)
#endif

#define DFOP2(NAME, OPCODE)	\
STARTFN (NAME);			\
	.set	noreorder;	\
	LDDBL1;			\
	nop;			\
	OPCODE	$f0,$f12;	\
	RETDBL;			\
	j	$31;		\
	nop;			\
	.set	reorder;	\
	ENDFN (NAME)
	
#ifdef L_m16negdf2
DFOP2(__mips16_negdf2, neg.d)
#endif
#ifdef L_m16absdf2
DFOP2(__mips16_absdf2, abs.d)
#endif

	
/* Conversions between single and double precision.  */

#ifdef L_m16extsfdf2
STARTFN (__mips16_extendsfdf2)
	.set	noreorder
	mtc1	$4,$f12
	nop
	cvt.d.s	$f0,$f12
	RETDBL
	j	$31
	nop
	.set	reorder
	ENDFN (__mips16_extendsfdf2)
#endif

#ifdef L_m16trdfsf2
STARTFN (__mips16_truncdfsf2)
	.set	noreorder
	LDDBL1
	nop
	cvt.s.d	$f0,$f12
	mfc1	$2,$f0
	j	$31
	nop
	.set	reorder
	ENDFN (__mips16_truncdfsf2)
#endif

/* Double precision comparisons.  */

/* This macro defines a function which loads two double precision
   values, performs a floating point comparison, and returns the
   specified values according to whether the comparison is true or
   false.  */

#define DFCMP(NAME, OPCODE, TRUE, FALSE)	\
STARTFN (NAME);					\
	LDDBL1;					\
	LDDBL2;					\
	OPCODE	$f12,$f14;			\
	li	$2,TRUE;			\
	bc1t	1f;				\
	li	$2,FALSE;			\
1:;						\
	j	$31;				\
	ENDFN (NAME)

/* This macro is like DFCMP, but it reverses the comparison.  */

#define DFREVCMP(NAME, OPCODE, TRUE, FALSE)	\
STARTFN (NAME);					\
	LDDBL1;					\
	LDDBL2;					\
	OPCODE	$f14,$f12;			\
	li	$2,TRUE;			\
	bc1t	1f;				\
	li	$2,FALSE;			\
1:;						\
	j	$31;				\
	ENDFN (NAME)

#ifdef L_m16eqdf2
DFCMP(__mips16_eqdf2, c.eq.d, 0, 1)
#endif
#ifdef L_m16nedf2
DFCMP(__mips16_nedf2, c.eq.d, 0, 1)
#endif
#ifdef L_m16gtdf2
DFREVCMP(__mips16_gtdf2, c.lt.d, 1, 0)
#endif
#ifdef L_m16gedf2
DFREVCMP(__mips16_gedf2, c.le.d, 0, -1)
#endif
#ifdef L_m16ledf2
DFCMP(__mips16_ledf2, c.le.d, 0, 1)
#endif
#ifdef L_m16ltdf2
DFCMP(__mips16_ltdf2, c.lt.d, -1, 0)
#endif

/* Double precision conversions.  */

#ifdef L_m16fltsidf
STARTFN (__mips16_floatsidf)
	.set	noreorder
	mtc1	$4,$f12
	nop
	cvt.d.w	$f0,$f12
	RETDBL
	j	$31
	nop
	.set	reorder
	ENDFN (__mips16_floatsidf)
#endif

#ifdef L_m16fixdfsi
STARTFN (__mips16_fixdfsi)
	.set	noreorder
	LDDBL1
	nop
	trunc.w.d $f0,$f12,$4
	mfc1	$2,$f0
	j	$31
	nop
	.set	reorder
	ENDFN (__mips16_fixdfsi)
#endif
#endif /* !__mips_single_float */

/* These functions are used to return floating point values from
   mips16 functions which do not use -mentry.  In this case we can
   put mtc1 in a jump delay slot, because we know that the next
   instruction will not refer to a floating point register.  */

#ifdef L_m16retsf
STARTFN (__mips16_ret_sf)
	.set	noreorder
	j	$31
	mtc1	$2,$f0
	.set	reorder
	ENDFN (__mips16_ret_sf)
#endif

#if !defined(__mips_single_float) && !defined(__SINGLE_FLOAT)
#ifdef L_m16retdf
STARTFN (__mips16_ret_df)
	.set	noreorder
#if defined(__mips64)
	j	$31
	dmtc1	$2,$f0
#elif defined(__mipsfp64)
	sw	$2,0($29)
	sw	$3,4($29)
	l.d	$f0,0($29) 
#elif defined(__MIPSEB__)	
	mtc1	$2,$f1
	j	$31
	mtc1	$3,$f0
#else	
	mtc1	$2,$f0
	j	$31
	mtc1	$3,$f1
#endif
	.set	reorder
	ENDFN (__mips16_ret_df)
#endif
#endif /* !__mips_single_float */

/* These functions are used by 16 bit code when calling via a function
   pointer.  They must copy the floating point arguments from the gp
   regs into the fp regs.  The function to call will be in $2.  The
   exact set of floating point arguments to copy is encoded in the
   function name; the final number is an fp_code, as described in
   mips.h in the comment about CUMULATIVE_ARGS.  */

#ifdef L_m16stub1
/* (float) */
STARTFN (__mips16_call_stub_1)
	.set	noreorder
	mtc1	$4,$f12
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_1)
#endif

#ifdef L_m16stub5
/* (float, float) */
STARTFN (__mips16_call_stub_5)
	.set	noreorder
	mtc1	$4,$f12
	mtc1	$5,$f14
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_5)
#endif

#if !defined(__mips_single_float) && !defined(__SINGLE_FLOAT)

#ifdef L_m16stub2
/* (double) */
STARTFN (__mips16_call_stub_2)
	.set	noreorder
	LDDBL1
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_2)
#endif

#ifdef L_m16stub6
/* (double, float) */
STARTFN (__mips16_call_stub_6)
	.set	noreorder
	LDDBL1
	mtc1	$6,$f14
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_6)
#endif

#ifdef L_m16stub9
/* (float, double) */
STARTFN (__mips16_call_stub_9)
	.set	noreorder
	mtc1	$4,$f12
	LDDBL2
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_9)
#endif

#ifdef L_m16stub10
/* (double, double) */
STARTFN (__mips16_call_stub_10)
	.set	noreorder
	LDDBL1
	LDDBL2
	j	$2
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_10)
#endif
#endif /* !__mips_single_float */

/* Now we have the same set of functions, except that this time the
   function being called returns an SFmode value.  The calling
   function will arrange to preserve $18, so these functions are free
   to use it to hold the return address.

   Note that we do not know whether the function we are calling is 16
   bit or 32 bit.  However, it does not matter, because 16 bit
   functions always return floating point values in both the gp and
   the fp regs.  It would be possible to check whether the function
   being called is 16 bits, in which case the copy is unnecessary;
   however, it's faster to always do the copy.  */

#ifdef L_m16stubsf0
/* () */
STARTFN (__mips16_call_stub_sf_0)
	.set	noreorder
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_0)
#endif

#ifdef L_m16stubsf1
/* (float) */
STARTFN (__mips16_call_stub_sf_1)
	.set	noreorder
	mtc1	$4,$f12
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_1)
#endif

#ifdef L_m16stubsf5
/* (float, float) */
STARTFN (__mips16_call_stub_sf_5)
	.set	noreorder
	mtc1	$4,$f12
	mtc1	$5,$f14
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_5)
#endif

#if !defined(__mips_single_float) && !defined(__SINGLE_FLOAT)
#ifdef L_m16stubsf2
/* (double) */
STARTFN (__mips16_call_stub_sf_2)
	.set	noreorder
	LDDBL1
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_2)
#endif

#ifdef L_m16stubsf6
/* (double, float) */
STARTFN (__mips16_call_stub_sf_6)
	.set	noreorder
	LDDBL1
	mtc1	$6,$f14
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_6)
#endif

#ifdef L_m16stubsf9
/* (float, double) */
STARTFN (__mips16_call_stub_sf_9)
	.set	noreorder
	mtc1	$4,$f12
	LDDBL2
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_9)
#endif

#ifdef L_m16stubsf10
/* (double, double) */
STARTFN (__mips16_call_stub_sf_10)
	.set	noreorder
	LDDBL1
	LDDBL2
	move	$18,$31
	jal	$2
	nop
	mfc1	$2,$f0
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_sf_10)
#endif

/* Now we have the same set of functions again, except that this time
   the function being called returns an DFmode value.  */

#ifdef L_m16stubdf0
/* () */
STARTFN (__mips16_call_stub_df_0)
	.set	noreorder
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_0)
#endif

#ifdef L_m16stubdf1
/* (float) */
STARTFN (__mips16_call_stub_df_1)
	.set	noreorder
	mtc1	$4,$f12
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_1)
#endif

#ifdef L_m16stubdf2
/* (double) */
STARTFN (__mips16_call_stub_df_2)
	.set	noreorder
	LDDBL1
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_2)
#endif

#ifdef L_m16stubdf5
/* (float, float) */
STARTFN (__mips16_call_stub_df_5)
	.set	noreorder
	mtc1	$4,$f12
	mtc1	$5,$f14
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_5)
#endif

#ifdef L_m16stubdf6
/* (double, float) */
STARTFN (__mips16_call_stub_df_6)
	.set	noreorder
	LDDBL1
	mtc1	$6,$f14
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_6)
#endif

#ifdef L_m16stubdf9
/* (float, double) */
STARTFN (__mips16_call_stub_df_9)
	.set	noreorder
	mtc1	$4,$f12
	LDDBL2
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_9)
#endif

#ifdef L_m16stubdf10
/* (double, double) */
STARTFN (__mips16_call_stub_df_10)
	.set	noreorder
	LDDBL1
	LDDBL2
	move	$18,$31
	jal	$2
	nop
	RETDBL
	j	$18
	nop
	.set	reorder
	ENDFN (__mips16_call_stub_df_10)
#endif
#endif /* !__mips_single_float */

