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
