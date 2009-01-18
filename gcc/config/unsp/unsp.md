; Constraints
; 'r' -> GENERAL_REGS
; 'b' -> BASE_REGS
; 'c' -> R3_REGS
; 'd' -> R4_REGS
; 'e' -> MUL_REGS
; 'f' -> GP_REGS
; 'h' -> R1R2_REGS
; 'I' -> (VALUE) >= 0 && (VALUE) <= 63
; 'J' -> (VALUE) >= 1 && (VALUE) <= 4
; 'K' -> (VALUE) >= 0 && (VALUE) <= 65535
; 'Q' -> direct16_memory_operand()
; 'R' -> non_direct16_memory_operand()
; 'S' -> lvalue_operand() [direct16 memory or reg]

;===============================================================================
;===============================================================================

(define_expand "movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand" "")
        (match_operand:QI 1 "general_operand" ""))]
  ""
  "
{
  /* Don't generate memory->memory moves, go through a register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[1]) != REG)
    operands[1] = force_reg (QImode, operands[1]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand" "")
        (match_operand:HI 1 "general_operand" ""))]
  ""
  "
{
  /* Don't generate memory->memory moves, go through a register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[1]) != REG)
    operands[1] = force_reg (HImode, operands[1]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "movhf"
  [(set (match_operand:HF 0 "nonimmediate_operand" "")
        (match_operand:HF 1 "general_operand" ""))]
  ""
  "
{
  /* Don't generate memory->memory moves, go through a register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[1]) != REG)
    operands[1] = force_reg (HFmode, operands[1]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);

    }
}")

;===============================================================================
;===============================================================================

(define_insn "movqi_all"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=r,m")
        (match_operand:QI 1 "general_operand" "rim,r"))]
  ""
  "*
{
  if (GET_CODE (operands[0]) == MEM
      && GET_CODE (XEXP (operands[0], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[0], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[0], 0), 0))
      && INTVAL (XEXP (XEXP (operands[0], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[0], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = GEN_INT (i);
      xops[2] = gen_rtx_MEM (QImode, gen_rtx (PLUS, QImode,
                                              xops[0], GEN_INT (j)));
      xops[3] = operands[1];

      if ((GET_CODE (operands[1]) == REG && REG_OK_FOR_BASE_P (operands[1])))
        {
          output_asm_insn (\"push r1 to [sp]\", xops);
          output_asm_insn (\"r1=bp\", xops);
          xops[3] = gen_rtx_REG (QImode, REG_R1);
        }

      output_asm_insn (\"%0+=%1\\t// movqi_all\", xops);
      output_asm_insn (\"%2=%3\", xops);
      output_asm_insn (\"%0-=%1\", xops);

      if ((GET_CODE (operands[1]) == REG && REG_OK_FOR_BASE_P (operands[1])))
        {
          output_asm_insn (\"pop r1 from [sp]\", xops);
        }
    }
  else if (GET_CODE (operands[1]) == MEM
      && GET_CODE (XEXP (operands[1], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
      && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[1], 0), 0)));
      xops[1] = GEN_INT (i);
      xops[2] = gen_rtx_MEM (QImode, gen_rtx (PLUS, QImode,
                                              xops[0], GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%0+=%1\\t// movqi_all\", xops);
      output_asm_insn (\"%3=%2\", xops);
      if ((GET_CODE (operands[1]) == REG && REG_OK_FOR_BASE_P (operands[1])))
        {
        }
      else
        {
          output_asm_insn (\"%0-=%1\", xops);
        }
    }
  else if (GET_CODE (operands[1]) == SYMBOL_REF
           && far_ptr_name (XSTR (operands[1], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[2];
      char name[60];

/*
      strcpy (name, \"*\");
      strcat (name, XSTR (operands[1], 0));
      strcat (name, \"_entry\");
*/
      sprintf (name, \"*%s_entry\", XSTR (operands[1], 0));
      xops[0] = operands[0];
      xops[1] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1\\t// QImode move, function pointer\", xops);
    }
  else if (GET_CODE (operands[1]) == CONST
           && GET_CODE (XEXP (operands[1], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[1], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[2];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[1], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[1], 0), 1)));
      output_asm_insn (\"%0=%1\\t// QImode move, function pointer\", xops);
    }
  else
    {
      output_asm_insn (\"%0=%1\\t// QImode move\", operands);
    }
  return \"\";
}")

;===============================================================================

(define_insn "movhi_mr1"
  [(set (match_operand:HI 0 "nonimmediate_operand" "=rm")
        (reg:HI 1))]
  ""
  "*
{
  rtx xops[6];

  xops[2] = gen_rtx_REG (QImode, REG_R1);
  xops[3] = gen_rtx_REG (QImode, REG_R2);

  if (GET_CODE (operands[0]) == REG)
    {
      xops[0] = operands[0];
      xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

      if (REGNO (xops[0]) == REGNO (xops[3]))
        {
          /* R3:R2 = R2:R1 */
          output_asm_insn (\"%1=%3\\t// HImode register to register move\", xops);
          output_asm_insn (\"%0=%2\", xops);
          return \"\";
        }
      output_asm_insn (\"%0=%2\\t// HImode register to register move\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PRE_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      
      output_asm_insn (\"%4=%4+%5\\t// [++RD]=RS HImode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD++]=RS HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_DEC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD--]=RS HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == REG)
    {
      if (REGNO (xops[2]) == REGNO (XEXP (operands[0], 0)) + 1)
        {
          /* [R2]=R1 => [R2]=R1; PUSH BP; BP=R2; [BP+1]=R2; POP BP */
          xops[0] = operands[0];
          xops[1] = XEXP (operands[0], 0);
          output_asm_insn (\"%0=%2\\t// [RD]=RS HImode, RD=RS+1\", xops);
          output_asm_insn (\"PUSH BP TO [SP]\\n\\tBP=%1\", xops);
          output_asm_insn (\"[BP+1]=%3\\n\\tPOP BP FROM [SP]\", xops);
          return \"\";
        }
      else
        {
          /* [R3]=R1 => [R3++]=R1; [R3--]=R2 */
          xops[0] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode, 
                                          XEXP (operands[0], 0)));
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (operands[0], 0)));

          output_asm_insn (\"%0=%2\\t// [RD]=RS HImode, RD!=RS+1\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[0], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[0], 0), 0))
           && INTVAL (XEXP (XEXP (operands[0], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[0], 0), 1)) <= 62)
        {
          xops[0] = operands[0];
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[0], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[0], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HImode [BP+#IM6]=RS\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[0], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[0] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j)));
          xops[1] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[0], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HImode [BP+#IM6]=RS, #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[0]))
    {
      xops[0] = operands[0];
      xops[1] = adj_offsettable_operand (operands[0], 1);

      output_asm_insn (\"%0=%2\\t// HImode [Label]=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}");

(define_insn "movhi_rr"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (match_operand:HI 1 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  if (REGNO (xops[0]) == REGNO (xops[3]))
    {
      /* R3:R2 = R2:R1 */
      output_asm_insn (\"%1=%3\\t// HImode register to register move\", xops);
      output_asm_insn (\"%0=%2\", xops);
      return \"\";
    }
  output_asm_insn (\"%0=%2\\t// HImode register to register move\", xops);
  output_asm_insn (\"%1=%3\", xops);
  return \"\";
}");

(define_insn "movhi_ri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (match_operand:HI 1 "immediate_operand" "i"))]
  ""
  "*
{
  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  split_double (operands[1], &xops[2], &xops[3]);

  output_asm_insn (\"%0=%2\\t// HImode immediate to register move\", xops);
  output_asm_insn (\"%1=%3\", xops);
  return \"\";
}");

(define_insn "movhi_rm"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (match_operand:HI 1 "memory_operand" "m"))]
  ""
  "*
{
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[1], 0)) == PRE_INC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%4=%4+%5\\t// RD=[++RS] HImode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == POST_INC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// RD=[RS++] HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == POST_DEC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// RD=[RS--] HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == REG)
    {
      xops[2] = XEXP (operands[1], 0);
      xops[3] = operands[1];
      xops[4] = gen_rtx_MEM (QImode, gen_rtx (POST_INC, QImode, xops[1]));
      xops[5] = gen_rtx_MEM (QImode, xops[1]);

      if (REGNO (xops[0]) == REGNO (xops[2]))
        {
          /* R1=[R1] => R2=R1; R1=[R2++]; R2=[R2] */
          output_asm_insn (\"%1=%2\\t// RD=[RS] HImode, RD==RS\", xops);
          output_asm_insn (\"%0=%4\", xops);
          output_asm_insn (\"%1=%5\", xops);
          return \"\";
        }
      if ((REGNO (xops[0]) + 1) == REGNO (xops[2]))
        {
          /* R1=[R2] => R1=[R2++]; R2=[R2] */
          output_asm_insn (\"%0=%4\\t// RD=[RS] HImode, RD+1=RS\", xops);
          output_asm_insn (\"%1=%5\", xops);
          return \"\";
        }
      /* R1=[R3] => R1=[R3++]; R2=[R3--] */
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, XEXP (operands[1], 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, XEXP (operands[1], 0)));

      output_asm_insn (\"%0=%2\\t// RD=[RS] HImode, RD!=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
           && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[1], 0), 1)) <= 62)
        {
          xops[2] = operands[1];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[1], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[1], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HImode RD=[BP+#IM6]\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[1], 0), 0),
                                           GEN_INT (j)));
          xops[3] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[1], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[1], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HImode RD=[BP+#IM6], #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[1]))
    {
      xops[2] = operands[1];
      xops[3] = adj_offsettable_operand (operands[1], 1);

      output_asm_insn (\"%0=%2\\t// HImode RD=[Label]\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}");

(define_insn "movhi_mr"
  [(set (match_operand:HI 0 "memory_operand" "=m")
        (match_operand:HI 1 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[6];

  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  if (GET_CODE (XEXP (operands[0], 0)) == PRE_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      
      output_asm_insn (\"%4=%4+%5\\t// [++RD]=RS HImode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD++]=RS HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_DEC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD--]=RS HImode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == REG)
    {
      if (REGNO (xops[2]) == REGNO (XEXP (operands[0], 0)) + 1)
        {
          /* [R2]=R1 => [R2]=R1; PUSH BP; BP=R2; [BP+1]=R2; POP BP */
          xops[0] = operands[0];
          xops[1] = XEXP (operands[0], 0);
          output_asm_insn (\"%0=%2\\t// [RD]=RS HImode, RD=RS+1\", xops);
          output_asm_insn (\"PUSH BP TO [SP]\\n\\tBP=%1\", xops);
          output_asm_insn (\"[BP+1]=%3\\n\\tPOP BP FROM [SP]\", xops);
          return \"\";
        }
      else
        {
          /* [R3]=R1 => [R3++]=R1; [R3--]=R2 */
          xops[0] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode, 
                                          XEXP (operands[0], 0)));
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (operands[0], 0)));

          output_asm_insn (\"%0=%2\\t// [RD]=RS HImode, RD!=RS+1\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[0], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[0], 0), 0))
           && INTVAL (XEXP (XEXP (operands[0], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[0], 0), 1)) <= 62)
        {
          xops[0] = operands[0];
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[0], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[0], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HImode [BP+#IM6]=RS\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[0], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[0] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j)));
          xops[1] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[0], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HImode [BP+#IM6]=RS, #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[0]))
    {
      xops[0] = operands[0];
      xops[1] = adj_offsettable_operand (operands[0], 1);

      output_asm_insn (\"%0=%2\\t// HImode [Label]=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}");

;===============================================================================

(define_insn "movhf_mr1"
  [(set (match_operand:HF 0 "nonimmediate_operand" "=rm")
        (reg:HF 1))]
  ""
  "*
{
  rtx xops[6];

  xops[2] = gen_rtx_REG (QImode, REG_R1);
  xops[3] = gen_rtx_REG (QImode, REG_R2);

  if (GET_CODE (operands[0]) == REG)
    {
      xops[0] = operands[0];
      xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

      if (REGNO (xops[0]) == REGNO (xops[3]))
        {
          /* R3:R2 = R2:R1 */
          output_asm_insn (\"%1=%3\\t// HFmode register to register move\", xops);
          output_asm_insn (\"%0=%2\", xops);
          return \"\";
        }
      output_asm_insn (\"%0=%2\\t// HFmode register to register move\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PRE_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      
      output_asm_insn (\"%4=%4+%5\\t// [++RD]=RS HFmode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD++]=RS HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_DEC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD--]=RS HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == REG)
    {
      if (REGNO (xops[2]) == REGNO (XEXP (operands[0], 0)) + 1)
        {
          /* [R2]=R1 => [R2]=R1; PUSH BP; BP=R2; [BP+1]=R2; POP BP */
          xops[0] = operands[0];
          xops[1] = XEXP (operands[0], 0);
          output_asm_insn (\"%0=%2\\t// [RD]=RS HFmode, RD=RS+1\", xops);
          output_asm_insn (\"PUSH BP TO [SP]\\n\\tBP=%1\", xops);
          output_asm_insn (\"[BP+1]=%3\\n\\tPOP BP FROM [SP]\", xops);
          return \"\";
        }
      else
        {
          /* [R3]=R1 => [R3++]=R1; [R3--]=R2 */
          xops[0] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode, 
                                          XEXP (operands[0], 0)));
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (operands[0], 0)));

          output_asm_insn (\"%0=%2\\t// [RD]=RS HFmode, RD!=RS+1\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[0], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[0], 0), 0))
           && INTVAL (XEXP (XEXP (operands[0], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[0], 0), 1)) <= 62)
        {
          xops[0] = operands[0];
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[0], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[0], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HFmode [BP+#IM6]=RS\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[0], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[0] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j)));
          xops[1] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[0], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HFmode [BP+#IM6]=RS, #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[0]))
    {
      xops[0] = operands[0];
      xops[1] = adj_offsettable_operand (operands[0], 1);

      output_asm_insn (\"%0=%2\\t// HFmode [Label]=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}")

(define_insn "movhf_rr"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (match_operand:HF 1 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  if (REGNO (xops[0]) == REGNO (xops[3]))
    {
      /* R3:R2 = R2:R1 */
      output_asm_insn (\"%1=%3\\t// HFmode register to register move\", xops);
      output_asm_insn (\"%0=%2\", xops);
      return \"\";
    }
  output_asm_insn (\"%0=%2\\t// HFmode register to register move\", xops);
  output_asm_insn (\"%1=%3\", xops);
  return \"\";
}")

(define_insn "movhf_ri"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (match_operand:HF 1 "immediate_operand" "E"))]
  ""
  "*
{
  rtx xops[4];
  REAL_VALUE_TYPE temp_real;
  int temp_int;

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  REAL_VALUE_FROM_CONST_DOUBLE (temp_real, operands[1]);
  REAL_VALUE_TO_TARGET_SINGLE (temp_real, temp_int);
  xops[2] = GEN_INT (temp_int & 0xffff);
  xops[3] = GEN_INT ((temp_int >>16) & 0xffff);

  output_asm_insn (\"%0=%2\\t// HFmode immediate to register move\", xops);
  output_asm_insn (\"%1=%3\", xops);
  return \"\";
}")

(define_insn "movhf_rm"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (match_operand:HF 1 "memory_operand" "m"))]
  ""
  "*
{
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[1], 0)) == PRE_INC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%4=%4+%5\\t// RD=[++RS] HFmode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == POST_INC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// RD=[RS++] HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == POST_DEC)
    {
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[1], 0), 0)));
      xops[4] = XEXP (XEXP (operands[1], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// RD=[RS--] HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == REG)
    {
      xops[2] = XEXP (operands[1], 0);
      xops[3] = operands[1];
      xops[4] = gen_rtx_MEM (QImode, gen_rtx (POST_INC, QImode, xops[1]));
      xops[5] = gen_rtx_MEM (QImode, xops[1]);

      if (REGNO (xops[0]) == REGNO (xops[2]))
        {
          /* R1=[R1] => R2=R1; R1=[R2++]; R2=[R2] */
          output_asm_insn (\"%1=%2\\t// RD=[RS] HFmode, RD==RS\", xops);
          output_asm_insn (\"%0=%4\", xops);
          output_asm_insn (\"%1=%5\", xops);
          return \"\";
        }
      if ((REGNO (xops[0]) + 1) == REGNO (xops[2]))
        {
          /* R1=[R2] => R1=[R2++]; R2=[R2] */
          output_asm_insn (\"%0=%4\\t// RD=[RS] HFmode, RD+1=RS\", xops);
          output_asm_insn (\"%1=%5\", xops);
          return \"\";
        }
      /* R1=[R3] => R1=[R3++]; R2=[R3--] */
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, XEXP (operands[1], 0)));
      xops[3] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, XEXP (operands[1], 0)));

      output_asm_insn (\"%0=%2\\t// RD=[RS] HFmode, RD!=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[1], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
           && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[1], 0), 1)) <= 62)
        {
          xops[2] = operands[1];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[1], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[1], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HFmode RD=[BP+#IM6]\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[1], 0), 0),
                                           GEN_INT (j)));
          xops[3] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[1], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[1], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HFmode RD=[BP+#IM6], #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[1]))
    {
      xops[2] = operands[1];
      xops[3] = adj_offsettable_operand (operands[1], 1);

      output_asm_insn (\"%0=%2\\t// HFmode RD=[Label]\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}")

(define_insn "movhf_mr"
  [(set (match_operand:HF 0 "memory_operand" "=m")
        (match_operand:HF 1 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[6];

  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  if (GET_CODE (XEXP (operands[0], 0)) == PRE_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      
      output_asm_insn (\"%4=%4+%5\\t// [++RD]=RS HFmode\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_INC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD++]=RS HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4+%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == POST_DEC)
    {
      xops[0] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_INC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[1] = gen_rtx_MEM (QImode,
                             gen_rtx (POST_DEC, QImode, 
                                      XEXP (XEXP (operands[0], 0), 0)));
      xops[4] = XEXP (XEXP (operands[0], 0), 0);
      xops[5] = const2_rtx;
      output_asm_insn (\"%0=%2\\t// [RD--]=RS HFmode\", xops);
      output_asm_insn (\"%1=%3\", xops);
      output_asm_insn (\"%4=%4-%5\", xops);
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == REG)
    {
      if (REGNO (xops[2]) == REGNO (XEXP (operands[0], 0)) + 1)
        {
          /* [R2]=R1 => [R2]=R1; PUSH BP; BP=R2; [BP+1]=R2; POP BP */
          xops[0] = operands[0];
          xops[1] = XEXP (operands[0], 0);
          output_asm_insn (\"%0=%2\\t// [RD]=RS HFmode, RD=RS+1\", xops);
          output_asm_insn (\"PUSH BP TO [SP]\\n\\tBP=%1\", xops);
          output_asm_insn (\"[BP+1]=%3\\n\\tPOP BP FROM [SP]\", xops);
          return \"\";
        }
      else
        {
          /* [R3]=R1 => [R3++]=R1; [R3--]=R2 */
          xops[0] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode, 
                                          XEXP (operands[0], 0)));
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (operands[0], 0)));

          output_asm_insn (\"%0=%2\\t// [RD]=RS HFmode, RD!=RS+1\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[0], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[0], 0), 0)) == REG
           && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[0], 0), 0))
           && INTVAL (XEXP (XEXP (operands[0], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[0], 0), 1)) <= 62)
        {
          xops[0] = operands[0];
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[0], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[0], 0), 1)) + 1)));

          output_asm_insn (\"%0=%2\\t// HFmode [BP+#IM6]=RS\", xops);
          output_asm_insn (\"%1=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;

          i = INTVAL (XEXP (XEXP (operands[0], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xops[0] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j)));
          xops[1] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           XEXP (XEXP (operands[0], 0), 0),
                                           GEN_INT (j + 1)));
          xops[4] = XEXP (XEXP (operands[0], 0), 0);
          xops[5] = GEN_INT (i);
          
          output_asm_insn (\"%4=%4+%5\\t// HFmode [BP+#IM6]=RS, #IM6>62\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"%1=%3\", xops);
          output_asm_insn (\"%4=%4-%5\", xops);
          
          return \"\";
        }
    }
  else if (offsettable_memref_p (operands[0]))
    {
      xops[0] = operands[0];
      xops[1] = adj_offsettable_operand (operands[0], 1);

      output_asm_insn (\"%0=%2\\t// HFmode [Label]=RS\", xops);
      output_asm_insn (\"%1=%3\", xops);
      return \"\";
    }
  else
    {
      abort ();
    }
}")

;===============================================================================
;===============================================================================

(define_expand "movstrictqi"
  [(set (strict_low_part (match_operand:QI 0 "nonimmediate_operand" ""))
        (match_operand:QI 1 "general_operand" ""))]
  ""
  "
{
  /* Don't generate memory->memory moves, go through a register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[1]) != REG)
    operands[1] = force_reg (QImode, operands[1]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  emit_insn (gen_movqi_all (operands[0], operands[1]));
  DONE;
}")

;===============================================================================

;(define_insn "movstrictqi_all"
;  [(set (strict_low_part (match_operand:QI 0 "nonimmediate_operand" "=rm"))
;        (match_operand:QI 1 "general_operand" "rim"))]
;  ""
;  "*
;{
;  emit_insn (gen_movqi_all (operands[0], operands[1]));
;  return \"\";
;}")

;===============================================================================
;===============================================================================

(define_expand "addqi3"
  [(set (match_operand:QI 0 "lvalue_operand" "")
        (plus:QI (match_operand:QI 1 "register_operand" "")
                 (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  /* If operands[0] is memory, operands[2] can only be register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[2]) != REG)
    operands[2] = force_reg (QImode, operands[2]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (GET_CODE (operands[0]) == REG
           && GET_CODE (operands[2]) != CONST_INT
           && ! direct16_memory_operand (operands[2], QImode))
    {
      if (GET_CODE (operands[2]) == REG)
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_addqi3_r0r (operands[0], operands[0], operands[2]));
          DONE;
        }
      else
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_addqi3_r0R (operands[0], operands[0], operands[2]));
          DONE;
        }
    }
}")

(define_expand "addhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (plus:HI (match_operand:HI 1 "register_operand" "")
                 (match_operand:HI 2 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (REGNO (operands[0]) != REGNO (operands[1])
      && GET_CODE (operands[2]) != CONST_INT
      && ! direct16_memory_operand (operands[2], HImode))
    {
      emit_insn (gen_movhi_rr (operands[0], operands[1]));
      emit_insn (gen_addhi3_r0R (operands[0], operands[0], operands[2]));
      DONE;
    }
}")

(define_expand "addhf3"
  [(set (match_operand:HF 0 "register_operand" "")
        (plus:HF (match_operand:HF 1 "register_operand" "")
                 (match_operand:HF 2 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_addf2\"),
                                 NULL_RTX, 1, HFmode, 2,
                                 operands[1], HFmode,
                                 operands[2], HFmode);
  equiv = gen_rtx (PLUS, HFmode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================
;===============================================================================

;(define_insn "addqi3_rrQ"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (plus:QI (match_operand:QI 1 "register_operand" "r")
;                 (match_operand:QI 2 "memory_operand" "Q")))]
;  ""
;  "*
;{
;  /* Rd = Rs ALU_OP [#IM16] */
;  return \"%0=%1+%2\";
;}")

(define_insn "addqi3_r0R"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (plus:QI (match_operand:QI 1 "register_operand" "0,r")
                 (match_operand:QI 2 "memory_operand" "R,Q")))]
  ""
  "*
{
  if (which_alternative == 1)
    {
      /* Rd = Rs ALU_OP [#IM16] */
      return \"%0=%1+%2\\t// addqi3_r0R\";
    }

  /* which_alternative == 0 */
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = GEN_INT (i);
      xops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
      xops[2] = gen_rtx_MEM (HImode,
                             gen_rtx (PLUS, QImode,
                                      xops[1],
                                      GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%1=%1+%0\", xops);
      output_asm_insn (\"%3+=%2\", xops);
      output_asm_insn (\"%1=%1-%0\", xops);
      return \"\";
    }

  return \"%0+=%2\\t// addqi3_r0R\";
}")

(define_insn "addqi3_r0r"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (plus:QI (match_operand:QI 1 "register_operand" "0")
                 (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */
  return \"%0+=%2\\t// addqi3_r0r\";
}")

;(define_insn "addqi3_rrr"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (plus:QI (match_operand:QI 1 "register_operand" "r")
;                 (match_operand:QI 2 "register_operand" "r")))]
;  ""
;  "*
;{
;  return \"%0=%1\\n\\t%0-=%2\";
;}")

(define_insn "addqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (plus:QI (match_operand:QI 1 "register_operand" "r")
                 (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[2], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[2], 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1+%2\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[2]) == CONST
           && GET_CODE (XEXP (operands[2], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[2], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[2], 0), 1)));
      output_asm_insn (\"%0=%1+%2\", xops);
      return \"\";
    }
  /* Rd = Rs ALU_OP #IM16 */
  return \"%0=%1+%2\";
}")

(define_insn "addqi3_Qrr"
  [(set (match_operand:QI 0 "direct16_memory_operand" "=Q")
        (plus:QI (match_operand:QI 1 "register_operand" "r")
                 (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  return \"%0=%1+%2\";
}")

;===============================================================================

(define_insn "addhi3_r0R"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (plus:HI (match_operand:HI 1 "register_operand" "0")
                 (match_operand:HI 2 "non_direct16_memory_operand" "R")))]
  ""
  "*
{
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[2], 0), 1)) <= 62)
        {
          xops[2] = operands[2];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[2], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

          output_asm_insn (\"%0+=%2\\t// HImode RD+=[BP+#IM6]\", xops);
          output_asm_insn (\"%1+=%3, Carry\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;
          rtx xxops[4];

          i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xxops[0] = GEN_INT (i);
          xxops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
          xxops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           xxops[1],
                                           GEN_INT (j)));
          xxops[3] = operands[0];

          output_asm_insn (\"%1=%1+%0\", xxops);
          operands[2] = xxops[2];
          {
            xops[2] = operands[2];
            xops[3] = gen_rtx_MEM (QImode,
                                   gen_rtx (PLUS, QImode,
                                            XEXP (XEXP (operands[2], 0), 0),
                                            GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

            output_asm_insn (\"%0+=%2\\t// HImode RD+=[BP+#IM6]\", xops);
            output_asm_insn (\"%1+=%3, Carry\", xops);
          }
          output_asm_insn (\"%1=%1-%0\", xxops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == REG)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (operands[2], 0)))
        {
          /* R1+=[R1] => R2+=[++R1];R1-=1;R1+=[R1];R2+=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1+=%2\\t// HImode RD+=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0+=%3\", xops);
          output_asm_insn (\"%1+=0, Carry\", xops);
        }
      else
        {
          /* R1+=[R2] => R1+=[R2++];R2+=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (operands[2], 0)));

          output_asm_insn (\"%0+=%2\\t// HImode RD+=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1+=%3, Carry\", xops);
        }
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_INC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1+=[R1] => R2+=[++R1];R1-=1;R1+=[R1];R2+=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1+=%2\\t// HImode RD+=[RS++], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0+=%3\", xops);
          output_asm_insn (\"%1+=0, Carry\", xops);
        }
      else
        {
          /* R1+=[R2] => R1+=[R2++];R2+=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0+=%2\\t// HImode RD+=[RS++], RD!=RS\", xops);
          output_asm_insn (\"%1+=%3, Carry\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_DEC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1+=[R1] => R2+=[++R1];R1-=1;R1+=[R1];R2+=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1+=%2\\t// HImode RD+=[RS--], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0+=%3\", xops);
          output_asm_insn (\"%1+=0, Carry\", xops);
        }
      else
        {
          /* R1+=[R2] => R1+=[R2++];R2+=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0+=%2\\t// HImode RD+=[RS--], RD!=RS\", xops);
          output_asm_insn (\"%1+=%3, Carry\", xops);
        }
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2-%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == PRE_INC)
    {
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1+=[R1] => R2+=[++R1];R1-=1;R1+=[R1];R2+=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1+=%2\\t// HImode RD+=[++RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0+=%3\", xops);
          output_asm_insn (\"%1+=0, Carry\", xops);
        }
      else
        {
          /* R1+=[R2] => R1+=[R2++];R2+=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0+=%2\\t// HImode RD+=[++RS], RD!=RS\", xops);
          output_asm_insn (\"%1+=%3, Carry\", xops);
        }
      return \"\";
    }
  else
    /* Unknown memory operands[2] */
    abort ();
}")

(define_insn "addhi3_r0r"
  [(set (match_operand:HI 0 "register_operand" "+r")
        (plus:HI (match_dup 0)
                 (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  output_asm_insn (\"%0+=%2\\t// HImode RD+=RS\", xops);
  output_asm_insn (\"%1+=%3, Carry\", xops);
  return \"\";
}")

(define_insn "addhi3_rri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (plus:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "immediate_operand" "i")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP #IM16 */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  split_double (operands[2], &xops[4], &xops[5]);

  output_asm_insn (\"%0=%2+%4\\t// HImode RD=RS+#IMM16\", xops);
  output_asm_insn (\"%1=%3+%5, Carry\", xops);
  return \"\";
}")

(define_insn "addhi3_rrQ"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (plus:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "direct16_memory_operand" "Q")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP [#IM16] */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = adj_offsettable_operand (operands[2], 1);

  output_asm_insn (\"%0=%2+%4\\t// HImode RD=RS+[#IM16]\", xops);
  output_asm_insn (\"%1=%3+%5, Carry\", xops);
  return \"\";
}")

(define_insn "addhi3_Qrr"
  [(set (match_operand:HI 0 "direct16_memory_operand" "=Q")
        (plus:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = adj_offsettable_operand (operands[0], 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0=%2+%4\\t// HImode [#IM16]=RD+RS\", xops);
  output_asm_insn (\"%1=%3+%5, Carry\", xops);
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "subqi3"
  [(set (match_operand:QI 0 "lvalue_operand" "")
        (minus:QI (match_operand:QI 1 "register_operand" "")
                  (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  /* If operands[0] is memory, operands[2] can only be register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[2]) != REG)
    operands[2] = force_reg (QImode, operands[2]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (GET_CODE (operands[0]) == REG
           && GET_CODE (operands[2]) != CONST_INT
           && ! direct16_memory_operand (operands[2], QImode))
    {
      if (GET_CODE (operands[2]) == REG)
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_subqi3_r0r (operands[0], operands[0], operands[2]));
          DONE;
        }
      else
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_subqi3_r0R (operands[0], operands[0], operands[2]));
          DONE;
        }
    }
}")

(define_expand "subhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (minus:HI (match_operand:HI 1 "register_operand" "")
                  (match_operand:HI 2 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (REGNO (operands[0]) != REGNO (operands[1])
      && GET_CODE (operands[2]) != CONST_INT
      && ! direct16_memory_operand (operands[2], HImode))
    {
      emit_insn (gen_movhi_rr (operands[0], operands[1]));
      emit_insn (gen_subhi3_r0all (operands[0], operands[0], operands[2]));
      DONE;
    }
}")

(define_expand "subhf3"
  [(set (match_operand:HF 0 "register_operand" "")
        (minus:SF (match_operand:HF 1 "register_operand" "")
                  (match_operand:HF 2 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_subf2\"),
                                 NULL_RTX, 1, HFmode, 2,
                                 operands[1], HFmode,
                                 operands[2], HFmode);
  equiv = gen_rtx (MINUS, HFmode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================
;===============================================================================

;(define_insn "subqi3_rrQ"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (minus:QI (match_operand:QI 1 "register_operand" "r")
;                  (match_operand:QI 2 "direct16_memory_operand" "Q")))]
;  ""
;  "*
;{
;  /* Rd = Rs ALU_OP [#IM16] */
;  return \"%0=%1-%2\";
;}")

(define_insn "subqi3_r0R"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (minus:QI (match_operand:QI 1 "register_operand" "0,r")
                  (match_operand:QI 2 "memory_operand" "R,Q")))]
  ""
  "*
{
  if (which_alternative == 1)
    {
      /* Rd = Rs ALU_OP [#IM16] */
      return \"%0=%1-%2\";
    }

  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = GEN_INT (i);
      xops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (PLUS, QImode,
                                      xops[1],
                                      GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%1=%1+%0\", xops);
      output_asm_insn (\"%3-=%2\", xops);
      output_asm_insn (\"%1=%1-%0\", xops);
      return \"\";
    }

  return \"%0-=%2\\t// subqi3_r0R %0=%1-%2\";
}")

(define_insn "subqi3_r0r"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (minus:QI (match_operand:QI 1 "register_operand" "0")
                  (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */
  return \"%0-=%2\";
}")

;(define_insn "subqi3_rrr"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (minus:QI (match_operand:QI 1 "register_operand" "r")
;                  (match_operand:QI 2 "register_operand" "r")))]
;  ""
;  "*
;{
;  return \"%0=%1\\n\\t%0-=%2\";
;}")

(define_insn "subqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (minus:QI (match_operand:QI 1 "register_operand" "r")
                  (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[2], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[2], 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1-%2\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[2]) == CONST
           && GET_CODE (XEXP (operands[2], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[2], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[2], 0), 1)));
      output_asm_insn (\"%0=%1-%2\", xops);
      return \"\";
    }


  /* Rd = Rs ALU_OP #IM16 */
  return \"%0=%1-%2\";
}")

(define_insn "subqi3_Qrr"
  [(set (match_operand:QI 0 "direct16_memory_operand" "=Q")
        (minus:QI (match_operand:QI 1 "register_operand" "r")
                  (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  return \"%0=%1-%2\";
}")

;===============================================================================

(define_insn "subhi3_r0all"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (minus:HI (match_operand:HI 1 "register_operand" "0")
                  (match_operand:HI 2 "general_operand" "rim")))]
  ""
  "*
{
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  if (GET_CODE (operands[2]) == MEM)
  {
  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[2], 0), 1)) <= 62)
        {
          xops[2] = operands[2];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[2], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

          output_asm_insn (\"%0-=%2\\t// HImode RD-=[BP+#IM6]\", xops);
          output_asm_insn (\"%1-=%3, Carry\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;
          rtx xxops[3];

          i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xxops[0] = GEN_INT (i);
          xxops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
          xxops[2] = gen_rtx_MEM (HImode,
                                  gen_rtx (PLUS, QImode,
                                           xxops[1],
                                           GEN_INT (j)));

          output_asm_insn (\"%1=%1+%0\", xxops);
          operands[2] = xxops[2];
          {
            xops[2] = operands[2];
            xops[3] = gen_rtx_MEM (QImode,
                                   gen_rtx (PLUS, QImode,
                                            XEXP (XEXP (operands[2], 0), 0),
                                            GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

            output_asm_insn (\"%0-=%2\\t// HImode RD-=[BP+#IM6]\", xops);
            output_asm_insn (\"%1-=%3, Carry\", xops);
          }
          output_asm_insn (\"%1=%1+%0\", xxops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == REG)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (operands[2], 0)))
        {
          /* R1-=[R1] => R2-=[++R1];R1-=1;R1-=[R1];R2-=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1-=%2\\t// HImode RD-=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0-=%3\", xops);
          output_asm_insn (\"%1-=0, Carry\", xops);
        }
      else
        {
          /* R1-=[R2] => R1-=[R2++];R2-=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (operands[2], 0)));

          output_asm_insn (\"%0-=%2\\t// HImode RD-=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1-=%3, Carry\", xops);
        }

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_INC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1-=[R1] => R2-=[++R1];R1-=1;R1-=[R1];R2-=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1-=%2\\t// HImode RD-=[RS++], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0-=%3\", xops);
          output_asm_insn (\"%1-=0, Carry\", xops);
        }
      else
        {
          /* R1-=[R2] => R1-=[R2++];R2-=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0-=%2\\t// HImode RD-=[RS++], RD!=RS\", xops);
          output_asm_insn (\"%1-=%3, Carry\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_DEC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1-=[R1] => R2-=[++R1];R1-=1;R1-=[R1];R2-=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1-=%2\\t// HImode RD-=[RS--], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0-=%3\", xops);
          output_asm_insn (\"%1-=0, Carry\", xops);
        }
      else
        {
          /* R1-=[R2] => R1-=[R2++];R2-=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0-=%2\\t// HImode RD-=[RS--], RD!=RS\", xops);
          output_asm_insn (\"%1-=%3, Carry\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2-%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == PRE_INC)
    {
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1-=[R1] => R2-=[++R1];R1-=1;R1-=[R1];R2-=0,Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1-=%2\\t// HImode RD-=[++RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0-=%3\", xops);
          output_asm_insn (\"%1-=0, Carry\", xops);
        }
      else
        {
          /* R1-=[R2] => R1-=[R2++];R2-=[R2--],Carry */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0-=%2\\t// HImode RD-=[++RS], RD!=RS\", xops);
          output_asm_insn (\"%1-=%3, Carry\", xops);
        }

      return \"\";
    }
  else
    {
      xops[2] = operands[2];
      xops[3] = adj_offsettable_operand (operands[2], 1);

      output_asm_insn (\"%0-=%2\\t// HImode RD-=[#IM16]\", xops);
      output_asm_insn (\"%1-=%3, Carry\", xops);
      return \"\";
    }
  }
  else if (GET_CODE (operands[2]) == REG)
  {
  xops[2] = operands[2];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0-=%2\\t// HImode RD-=RS\", xops);
  output_asm_insn (\"%1-=%3, Carry\", xops);
  return \"\";
  }
  else if (GET_CODE (operands[2]) == CONST_INT)
  {
  split_double (operands[2], &xops[2], &xops[3]);

  output_asm_insn (\"%0-=%2\\t// HImode RD-=#IMM16\", xops);
  output_asm_insn (\"%1-=%3, Carry\", xops);
  return \"\";
  }
  else
  {
    abort ();
  }
}")

(define_insn "subhi3_r0r"
  [(set (match_operand:HI 0 "register_operand" "+r")
        (minus:HI (match_dup 0)
                  (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  output_asm_insn (\"%0-=%2\\t// HImode RD-=RS\", xops);
  output_asm_insn (\"%1-=%3, Carry\", xops);
  return \"\";
}")

(define_insn "subhi3_rri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (minus:HI (match_operand:HI 1 "register_operand" "r")
                  (match_operand:HI 2 "immediate_operand" "i")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP #IM16 */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  split_double (operands[2], &xops[4], &xops[5]);

  output_asm_insn (\"%0=%2-%4\\t// HImode RD=RS-#IMM16\", xops);
  output_asm_insn (\"%1=%3-%5, Carry\", xops);
  return \"\";
}")

(define_insn "subhi3_rrQ"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (minus:HI (match_operand:HI 1 "register_operand" "r")
                  (match_operand:HI 2 "direct16_memory_operand" "Q")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP [#IM16] */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = adj_offsettable_operand (operands[2], 1);

  output_asm_insn (\"%0=%2-%4\\t// HImode RD=RS-[#IM16]\", xops);
  output_asm_insn (\"%1=%3-%5, Carry\", xops);
  return \"\";
}")

(define_insn "subhi3_Qrr"
  [(set (match_operand:HI 0 "direct16_memory_operand" "=Q")
        (minus:HI (match_operand:HI 1 "register_operand" "r")
                  (match_operand:HI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = adj_offsettable_operand (operands[0], 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0=%2-%4\\t// HImode [#IM16]=RD-RS\", xops);
  output_asm_insn (\"%1=%3-%5, Carry\", xops);
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "mulqi3"
  [(set (match_operand:QI 0 "register_operand" "=c" )
        (mult:QI (match_operand:QI 1 "register_operand" "%r" )
                 (match_operand:QI 2 "register_operand" "r" )))
   (clobber (match_scratch:SI 3 "=d"))]
  ""
  "
{
  emit_insn (gen_mulqi3_all (operands[0], operands[1], operands[2]));
  DONE;
}")

(define_insn "mulqi3_all"
  [(set (match_operand:QI 0 "register_operand" "=c" )
        (mult:QI (match_operand:QI 1 "register_operand" "%r" )
                 (match_operand:QI 2 "register_operand" "r" )))
   (clobber (match_scratch:QI 3 "=d"))]
  ""
  "*
{
  return \"mr=%1*%2\\t// r3=%1*%2 16bit=16bit*16bit\";
}")

(define_expand "mulhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (mult:HI (match_operand:HI 1 "register_operand" "%r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_muli2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], HImode);
  equiv = gen_rtx (MULT, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "mulhf3"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (mult:HF (match_operand:HF 1 "register_operand" "r")
                 (match_operand:HF 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_mulf2\"),
                                 NULL_RTX, 1, HFmode, 2,
                                 operands[1], HFmode,
                                 operands[2], HFmode);
  equiv = gen_rtx (MULT, HFmode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================
;===============================================================================

(define_expand "divqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (div:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_divi1\"),
                                 NULL_RTX, 1, QImode, 2,
                                 operands[1], QImode,
                                 operands[2], QImode);
  equiv = gen_rtx (DIV, QImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "divhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (div:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_divi2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], HImode);
  equiv = gen_rtx (DIV, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "divhf3"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (div:HF (match_operand:HF 1 "register_operand" "r")
                (match_operand:HF 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_divf2\"),
                                 NULL_RTX, 1, HFmode, 2,
                                 operands[1], HFmode,
                                 operands[2], HFmode);
  equiv = gen_rtx (DIV, HFmode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================
;===============================================================================

(define_expand "udivqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (udiv:QI (match_operand:QI 1 "register_operand" "r")
                 (match_operand:QI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_divu1\"),
                                 NULL_RTX, 1, QImode, 2,
                                 operands[1], QImode,
                                 operands[2], QImode);
  equiv = gen_rtx (UDIV, QImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "udivhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (udiv:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_divu2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], HImode);
  equiv = gen_rtx (UDIV, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================
;===============================================================================

(define_expand "modqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mod:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_modi1\"),
                                 NULL_RTX, 1, QImode, 2,
                                 operands[1], QImode,
                                 operands[2], QImode);
  equiv = gen_rtx (MOD, QImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

(define_expand "modhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (mod:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_modi2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], HImode);
  equiv = gen_rtx (MOD, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================
;===============================================================================

(define_expand "umodqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (umod:QI (match_operand:QI 1 "register_operand" "r")
                 (match_operand:QI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_modu1\"),
                                 NULL_RTX, 1, QImode, 2,
                                 operands[1], QImode,
                                 operands[2], QImode);
  equiv = gen_rtx (UMOD, QImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

(define_expand "umodhi3"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (umod:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_modu2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], HImode);
  equiv = gen_rtx (UMOD, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================
;===============================================================================

(define_expand "andqi3"
  [(set (match_operand:QI 0 "lvalue_operand" "")
        (and:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  /* If operands[0] is memory, operands[2] can only be register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[2]) != REG)
    operands[2] = force_reg (QImode, operands[2]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (GET_CODE (operands[0]) == REG
           && REGNO (operands[0]) != REGNO (operands[1])
           && GET_CODE (operands[2]) != CONST_INT
           && ! direct16_memory_operand (operands[2], QImode))
    {
      if (GET_CODE (operands[2]) == REG)
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_andqi3_r0r (operands[0], operands[0], operands[2]));
          DONE;
        }
      else
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_andqi3_r0R (operands[0], operands[0], operands[2]));
          DONE;
        }
    }
}")

(define_expand "andhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (and:HI (match_operand:HI 1 "register_operand" "")
                (match_operand:HI 2 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (REGNO (operands[0]) != REGNO (operands[1])
      && GET_CODE (operands[2]) != CONST_INT
      && ! direct16_memory_operand (operands[2], HImode))
    {
      emit_insn (gen_movhi_rr (operands[0], operands[1]));
      emit_insn (gen_andhi3_r0R (operands[0], operands[0], operands[2]));
      DONE;
    }
}")

;===============================================================================

;(define_insn "andqi3_rrQ"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (and:QI (match_operand:QI 1 "register_operand" "r")
;                (match_operand:QI 2 "direct16_memory_operand" "Q")))]
;  ""
;  "*
;{
;  /* Rd = Rs ALU_OP [#IM16] */
;  return \"%0=%1&%2\";
;}")

(define_insn "andqi3_r0R"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (and:QI (match_operand:QI 1 "register_operand" "0,r")
                (match_operand:QI 2 "memory_operand" "R,Q")))]
  ""
  "*
{
  if (which_alternative == 1)
    {
      /* Rd = Rs ALU_OP [#IM16] */
      return \"%0=%1&%2\";
    }

  /* which_alternative == 0 */
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = GEN_INT (i);
      xops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (PLUS, QImode,
                                      xops[1],
                                      GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%1=%1+%0\", xops);
      output_asm_insn (\"%3&=%2\", xops);
      output_asm_insn (\"%1=%1-%0\", xops);

      return \"\";
    }

  return \"%0&=%2\\t// andqi3_r0R\";
}")

(define_insn "andqi3_r0r"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (and:QI (match_operand:QI 1 "register_operand" "0")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */
  return \"%0&=%2\";
}")

(define_insn "andqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (and:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[2], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[2], 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1&%2\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[2]) == CONST
           && GET_CODE (XEXP (operands[2], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[2], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[2], 0), 1)));
      output_asm_insn (\"%0=%1&%2\", xops);
      return \"\";
    }

  /* Rd = Rs ALU_OP #IM16 */
  return \"%0=%1&%2\";
}")

(define_insn "andqi3_Qrr"
  [(set (match_operand:QI 0 "direct16_memory_operand" "=Q")
        (and:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  return \"%0=%1&%2\";
}")

;===============================================================================

(define_insn "andhi3_r0R"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (and:HI (match_operand:HI 1 "register_operand" "0")
                (match_operand:HI 2 "non_direct16_memory_operand" "R")))]
  ""
  "*
{
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[2], 0), 1)) <= 62)
        {
          xops[2] = operands[2];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[2], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

          output_asm_insn (\"%0&=%2\\t// HImode RD&=[BP+#IM6]\", xops);
          output_asm_insn (\"%1&=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;
          rtx xxops[3];

          i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xxops[0] = GEN_INT (i);
          xxops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
          xxops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           xxops[1],
                                           GEN_INT (j)));

          output_asm_insn (\"%1=%1+%0\", xxops);
          operands[2] = xxops[2];
          {
            xops[2] = operands[2];
            xops[3] = gen_rtx_MEM (QImode,
                                   gen_rtx (PLUS, QImode,
                                            XEXP (XEXP (operands[2], 0), 0),
                                            GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

            output_asm_insn (\"%0&=%2\\t// HImode RD&=[BP+#IM6]\", xops);
            output_asm_insn (\"%1&=%3\", xops);
          }
          output_asm_insn (\"%1=%1-%0\", xxops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == REG)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (operands[2], 0)))
        {
          /* R1&=[R1] => R2&=[++R1];R1-=1;R1&=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1&=%2\\t// HImode RD&=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0&=%3\", xops);
        }
      else
        {
          /* R1&=[R2] => R1&=[R2++];R2&=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (operands[2], 0)));

          output_asm_insn (\"%0&=%2\\t// HImode RD&=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1&=%3\", xops);
        }
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_INC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1&=[R1] => R2&=[++R1];R1-=1;R1&=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1&=%2\\t// HImode RD&=[RS++], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0&=%3\", xops);
        }
      else
        {
          /* R1&=[R2] => R1&=[R2++];R2&=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0&=%2\\t// HImode RD&=[RS++], RD!=RS\", xops);
          output_asm_insn (\"%1&=%3\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_DEC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1&=[R1] => R2&=[++R1];R1-=1;R1&=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1&=%2\\t// HImode RD&=[RS--], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0&=%3\", xops);
        }
      else
        {
          /* R1&=[R2] => R1&=[R2++];R2&=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0&=%2\\t// HImode RD&=[RS--], RD!=RS\", xops);
          output_asm_insn (\"%1&=%3\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2-%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == PRE_INC)
    {
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1&=[R1] => R2&=[++R1];R1-=1;R1&=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1&=%2\\t// HImode RD&=[++RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0&=%3\", xops);
        }
      else
        {
          /* R1&=[R2] => R1&=[R2++];R2&=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0&=%2\\t// HImode RD&=[++RS], RD!=RS\", xops);
          output_asm_insn (\"%1&=%3\", xops);
        }
      return \"\";
    }
  else
    /* Unknown memory operands[2] */
    abort ();
}")

(define_insn "andhi3_r0r"
  [(set (match_operand:HI 0 "register_operand" "+r")
        (and:HI (match_dup 0)
                (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  output_asm_insn (\"%0&=%2\\t// HImode RD&=RS\", xops);
  output_asm_insn (\"%1&=%3\", xops);
  return \"\";
}")

(define_insn "andhi3_rri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (and:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "immediate_operand" "i")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP #IM16 */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  split_double (operands[2], &xops[4], &xops[5]);

  output_asm_insn (\"%0=%2&%4\\t// HImode RD=RS&#IMM16\", xops);
  output_asm_insn (\"%1=%3&%5\", xops);
  return \"\";
}")

(define_insn "andhi3_rrQ"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (and:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "direct16_memory_operand" "Q")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP [#IM16] */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = adj_offsettable_operand (operands[2], 1);

  output_asm_insn (\"%0=%2&%4\\t// HImode RD=RS&[#IM16]\", xops);
  output_asm_insn (\"%1=%3&%5\", xops);
  return \"\";
}")

(define_insn "andhi3_Qrr"
  [(set (match_operand:HI 0 "direct16_memory_operand" "=Q")
        (and:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = adj_offsettable_operand (operands[0], 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0=%2&%4\\t// HImode [#IM16]=RD&RS\", xops);
  output_asm_insn (\"%1=%3&%5\", xops);
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "iorqi3"
  [(set (match_operand:QI 0 "lvalue_operand" "")
        (ior:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  /* If operands[0] is memory, operands[2] can only be register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[2]) != REG)
    operands[2] = force_reg (QImode, operands[2]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (GET_CODE (operands[0]) == REG
           && REGNO (operands[0]) != REGNO (operands[1])
           && GET_CODE (operands[2]) != CONST_INT
           && ! direct16_memory_operand (operands[2], QImode))
    {
      if (GET_CODE (operands[2]) == REG)
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_iorqi3_r0r (operands[0], operands[0], operands[2]));
          DONE;
        }
      else
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_iorqi3_r0R (operands[0], operands[0], operands[2]));
          DONE;
        }
    }
}")

(define_expand "iorhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (ior:HI (match_operand:HI 1 "register_operand" "")
                (match_operand:HI 2 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (REGNO (operands[0]) != REGNO (operands[1])
      && GET_CODE (operands[2]) != CONST_INT
      && ! direct16_memory_operand (operands[2], HImode))
    {
      emit_insn (gen_movhi_rr (operands[0], operands[1]));
      emit_insn (gen_iorhi3_r0R (operands[0], operands[0], operands[2]));
      DONE;
    }
}")

;===============================================================================

;(define_insn "iorqi3_rrQ"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (ior:QI (match_operand:QI 1 "register_operand" "r")
;                (match_operand:QI 2 "direct16_memory_operand" "Q")))]
;  ""
;  "*
;{
;  /* Rd = Rs ALU_OP [#IM16] */
;  return \"%0=%1|%2\";
;}")

(define_insn "iorqi3_r0R"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (ior:QI (match_operand:QI 1 "register_operand" "0,r")
                (match_operand:QI 2 "memory_operand" "R,Q")))]
  ""
  "*
{
  if (which_alternative == 1)
    {
      /* Rd = Rs ALU_OP [#IM16] */
      return \"%0=%1|%2\";
    }

  /* which_alternative == 0 */
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = GEN_INT (i);
      xops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (PLUS, QImode,
                                      xops[1],
                                      GEN_INT (j)));
      xops[4] = operands[0];

      output_asm_insn (\"%1=%1+%0\", xops);
      output_asm_insn (\"%4|=%2\", xops);
      output_asm_insn (\"%1=%1-%0\", xops);
      return \"\";
    }

  return \"%0|=%2\\t// iorqi3_r0R\";
}")

(define_insn "iorqi3_r0r"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ior:QI (match_operand:QI 1 "register_operand" "0")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */
  return \"%0|=%2\";
}")

(define_insn "iorqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ior:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[2], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[2], 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1|%2\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[2]) == CONST
           && GET_CODE (XEXP (operands[2], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[2], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[2], 0), 1)));
      output_asm_insn (\"%0=%1|%2\", xops);
      return \"\";
    }

  /* Rd = Rs ALU_OP #IM16 */
  return \"%0=%1|%2\";
}")

(define_insn "iorqi3_Qrr"
  [(set (match_operand:QI 0 "direct16_memory_operand" "=Q")
        (ior:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  return \"%0=%1|%2\";
}")

;===============================================================================

(define_insn "iorhi3_r0R"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ior:HI (match_operand:HI 1 "register_operand" "0")
                (match_operand:HI 2 "non_direct16_memory_operand" "R")))]
  ""
  "*
{
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[2], 0), 1)) <= 62)
        {
          xops[2] = operands[2];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[2], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

          output_asm_insn (\"%0|=%2\\t// HImode RD|=[BP+#IM6]\", xops);
          output_asm_insn (\"%1|=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;
          rtx xxops[3];

          i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xxops[0] = GEN_INT (i);
          xxops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
          xxops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           xxops[1],
                                           GEN_INT (j)));

          output_asm_insn (\"%1=%1+%0\", xxops);
          operands[2] = xxops[2];
          {
            xops[2] = operands[2];
            xops[3] = gen_rtx_MEM (QImode,
                                   gen_rtx (PLUS, QImode,
                                            XEXP (XEXP (operands[2], 0), 0),
                                            GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

            output_asm_insn (\"%0|=%2\\t// HImode RD|=[BP+#IM6]\", xops);
            output_asm_insn (\"%1|=%3\", xops);
          }
          output_asm_insn (\"%1=%1-%0\", xxops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == REG)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (operands[2], 0)))
        {
          /* R1|=[R1] => R2|=[++R1];R1-=1;R1|=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1|=%2\\t// HImode RD|=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0|=%3\", xops);
        }
      else
        {
          /* R1|=[R2] => R1|=[R2++];R2|=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (operands[2], 0)));

          output_asm_insn (\"%0|=%2\\t// HImode RD|=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1|=%3\", xops);
        }
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_INC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1|=[R1] => R2|=[++R1];R1-=1;R1|=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1|=%2\\t// HImode RD|=[RS++], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0|=%3\", xops);
        }
      else
        {
          /* R1|=[R2] => R1|=[R2++];R2|=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0|=%2\\t// HImode RD|=[RS++], RD!=RS\", xops);
          output_asm_insn (\"%1|=%3\", xops);
        }

      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_DEC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1|=[R1] => R2|=[++R1];R1-=1;R1|=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1|=%2\\t// HImode RD|=[RS--], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0|=%3\", xops);
        }
      else
        {
          /* R1|=[R2] => R1|=[R2++];R2|=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0|=%2\\t// HImode RD|=[RS--], RD!=RS\", xops);
          output_asm_insn (\"%1|=%3\", xops);
        }
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2-%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == PRE_INC)
    {
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1|=[R1] => R2|=[++R1];R1-=1;R1|=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1|=%2\\t// HImode RD|=[++RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0|=%3\", xops);
        }
      else
        {
          /* R1|=[R2] => R1|=[R2++];R2|=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0|=%2\\t// HImode RD|=[++RS], RD!=RS\", xops);
          output_asm_insn (\"%1|=%3\", xops);
        }
      return \"\";
    }
  else
    /* Unknown memory operands[2] */
    abort ();
}")

(define_insn "iorhi3_r0r"
  [(set (match_operand:HI 0 "register_operand" "+r")
        (ior:HI (match_dup 0)
                (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  output_asm_insn (\"%0|=%2\\t// HImode RD|=RS\", xops);
  output_asm_insn (\"%1|=%3\", xops);
  return \"\";
}")

(define_insn "iorhi3_rri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ior:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "immediate_operand" "i")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP #IM16 */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  split_double (operands[2], &xops[4], &xops[5]);

  output_asm_insn (\"%0=%2|%4\\t// HImode RD=RS|#IMM16\", xops);
  output_asm_insn (\"%1=%3|%5\", xops);
  return \"\";
}")

(define_insn "iorhi3_rrQ"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (ior:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "direct16_memory_operand" "Q")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP [#IM16] */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = adj_offsettable_operand (operands[2], 1);

  output_asm_insn (\"%0=%2|%4\\t// HImode RD=RS|[#IM16]\", xops);
  output_asm_insn (\"%1=%3|%5\", xops);
  return \"\";
}")

(define_insn "iorhi3_Qrr"
  [(set (match_operand:HI 0 "direct16_memory_operand" "=Q")
        (ior:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = adj_offsettable_operand (operands[0], 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0=%2|%4\\t// HImode [#IM16]=RD|RS\", xops);
  output_asm_insn (\"%1=%3|%5\", xops);
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "xorqi3"
  [(set (match_operand:QI 0 "lvalue_operand" "")
        (xor:QI (match_operand:QI 1 "register_operand" "")
                (match_operand:QI 2 "general_operand" "")))]
  ""
  "
{
  /* If operands[0] is memory, operands[2] can only be register */
  if (no_new_pseudos == 0
      && GET_CODE (operands[0]) == MEM
      && GET_CODE (operands[2]) != REG)
    operands[2] = force_reg (QImode, operands[2]);

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (GET_CODE (operands[0]) == REG
           && REGNO (operands[0]) != REGNO (operands[1])
           && GET_CODE (operands[2]) != CONST_INT
           && ! direct16_memory_operand (operands[2], QImode))
    {
      if (GET_CODE (operands[2]) == REG)
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_xorqi3_r0r (operands[0], operands[0], operands[2]));
          DONE;
        }
      else
        {
          emit_insn (gen_movqi_all (operands[0], operands[1]));
          emit_insn (gen_xorqi3_r0R (operands[0], operands[0], operands[2]));
          DONE;
        }
    }
}")

(define_expand "xorhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (xor:HI (match_operand:HI 1 "register_operand" "")
                (match_operand:HI 2 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[2], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  if (REGNO (operands[0]) != REGNO (operands[1])
      && GET_CODE (operands[2]) != CONST_INT
      && ! direct16_memory_operand (operands[2], HImode))
    {
      emit_insn (gen_movhi_rr (operands[0], operands[1]));
      emit_insn (gen_xorhi3_r0R (operands[0], operands[0], operands[2]));
      DONE;
    }
}")

;===============================================================================

;(define_insn "xorqi3_rrQ"
;  [(set (match_operand:QI 0 "register_operand" "=r")
;        (xor:QI (match_operand:QI 1 "register_operand" "r")
;                (match_operand:QI 2 "direct16_memory_operand" "Q")))]
;  ""
;  "*
;{
;  /* Rd = Rs ALU_OP [#IM16] */
;  return \"%0=%1^%2\";
;}")

(define_insn "xorqi3_r0R"
  [(set (match_operand:QI 0 "register_operand" "=r,r")
        (xor:QI (match_operand:QI 1 "register_operand" "0,r")
                (match_operand:QI 2 "memory_operand" "R,Q")))]
  ""
  "*
{
  if (which_alternative == 1)
    {
      /* Rd = Rs ALU_OP [#IM16] */
      return \"%0=%1^%2\";
    }

  /* which_alternative == 0 */
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = GEN_INT (i);
      xops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
      xops[2] = gen_rtx_MEM (QImode,
                             gen_rtx (PLUS, QImode,
                                      xops[1],
                                      GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%1=%1+%0\", xops);
      output_asm_insn (\"%3^=%2\", xops);
      output_asm_insn (\"%1=%1-%0\", xops);

      return \"\";
    }

  return \"%0^=%2\\t// xorqi3_r0R\";
}")

(define_insn "xorqi3_r0r"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (xor:QI (match_operand:QI 1 "register_operand" "0")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */
  return \"%0^=%2\";
}")

(define_insn "xorqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (xor:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[2], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[2], 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"%0=%1^%2\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[2]) == CONST
           && GET_CODE (XEXP (operands[2], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[2], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[3];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = operands[1];
      xops[2] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[2], 0), 1)));
      output_asm_insn (\"%0=%1^%2\", xops);
      return \"\";
    }

  /* Rd = Rs ALU_OP #IM16 */
  return \"%0=%1^%2\";
}")

(define_insn "xorqi3_Qrr"
  [(set (match_operand:QI 0 "direct16_memory_operand" "=Q")
        (xor:QI (match_operand:QI 1 "register_operand" "r")
                (match_operand:QI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  return \"%0=%1^%2\";
}")

;===============================================================================

(define_insn "xorhi3_r0R"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (xor:HI (match_operand:HI 1 "register_operand" "0")
                (match_operand:HI 2 "non_direct16_memory_operand" "R")))]
  ""
  "*
{
  /* Rd ALU_OP= [BP+#IM6]
     Rd ALU_OP= DS:[Rs]
     Rd ALU_OP= DS:[Rs++]
     Rd ALU_OP= DS:[Rs--]
     Rd ALU_OP= DS:[++Rs] */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  if (GET_CODE (XEXP (operands[2], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[2], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[2], 0), 0))
      && GET_CODE (XEXP (XEXP (operands[2], 0), 1)) == CONST_INT
      && INTVAL (XEXP (XEXP (operands[2], 0), 1)) >= 0)
    {
      if (INTVAL (XEXP (XEXP (operands[2], 0), 1)) <= 62)
        {
          xops[2] = operands[2];
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[2], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

          output_asm_insn (\"%0^=%2\\t// HImode RD^=[BP+#IM6]\", xops);
          output_asm_insn (\"%1^=%3\", xops);
          return \"\";
        }
      else
        {
          int i;
          int j;
          rtx xxops[3];

          i = INTVAL (XEXP (XEXP (operands[2], 0), 1));
          j = i % 64;
          if (j == 63) j = 0;
          i = i - j;

          xxops[0] = GEN_INT (i);
          xxops[1] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[2], 0), 0)));
          xxops[2] = gen_rtx_MEM (QImode,
                                  gen_rtx (PLUS, QImode,
                                           xxops[1],
                                           GEN_INT (j)));

          output_asm_insn (\"%1=%1+%0\", xxops);
          operands[2] = xxops[2];
          {
            xops[2] = operands[2];
            xops[3] = gen_rtx_MEM (QImode,
                                   gen_rtx (PLUS, QImode,
                                            XEXP (XEXP (operands[2], 0), 0),
                                            GEN_INT (INTVAL (XEXP (XEXP (operands[2], 0), 1)) + 1)));

            output_asm_insn (\"%0^=%2\\t// HImode RD^=[BP+#IM6]\", xops);
            output_asm_insn (\"%1^=%3\", xops);
            return \"\";
          }
          output_asm_insn (\"%1=%1-%0\", xxops);
          return \"\";
        }
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == REG)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (operands[2], 0)))
        {
          /* R1^=[R1] => R2^=[++R1];R1-=1;R1^=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1^=%2\\t// HImode RD^=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0^=%3\", xops);
        }
      else
        {
          /* R1^=[R2] => R1^=[R2++];R2^=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (operands[2], 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (operands[2], 0)));

          output_asm_insn (\"%0^=%2\\t// HImode RD^=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1^=%3\", xops);
        }
      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_INC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1^=[R1] => R2^=[++R1];R1-=1;R1^=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1^=%2\\t// HImode RD^=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0^=%3\", xops);
        }
      else
        {
          /* R1^=[R2] => R1^=[R2++];R2^=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0^=%2\\t// HImode RD^=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1^=%3\", xops);
        }
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == POST_DEC)
    {
      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1^=[R1] => R2^=[++R1];R1-=1;R1^=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1^=%2\\t// HImode RD^=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0^=%3\", xops);
        }
      else
        {
          /* R1^=[R2] => R1^=[R2++];R2^=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0^=%2\\t// HImode RD^=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1^=%3\", xops);
        }
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2-%3\", xops);

      return \"\";
    }
  else if (GET_CODE (XEXP (operands[2], 0)) == PRE_INC)
    {
      xops[2] = XEXP (XEXP (operands[2], 0), 0);
      xops[3] = const2_rtx;
      output_asm_insn (\"%2=%2+%3\", xops);

      if (REGNO (operands[0]) == REGNO (XEXP (XEXP (operands[2], 0), 0)))
        {
          /* R1^=[R1] => R2^=[++R1];R1-=1;R1^=[R1] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (PRE_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = operands[2];

          output_asm_insn (\"%1^=%2\\t// HImode RD^=[RS], RD=RS\", xops);
          output_asm_insn (\"%0-=1\", xops);
          output_asm_insn (\"%0^=%3\", xops);
        }
      else
        {
          /* R1^=[R2] => R1^=[R2++];R2^=[R2--] */
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_INC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));
          xops[3] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode,
                                          XEXP (XEXP (operands[2], 0), 0)));

          output_asm_insn (\"%0^=%2\\t// HImode RD^=[RS], RD!=RS\", xops);
          output_asm_insn (\"%1^=%3\", xops);
        }
      return \"\";
    }
  else
    /* Unknown memory operands[2] */
    abort ();
}")

(define_insn "xorhi3_r0r"
  [(set (match_operand:HI 0 "register_operand" "+r")
        (xor:HI (match_dup 0)
                (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  /* Rd ALU_OP= Rs */

  rtx xops[4];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

  output_asm_insn (\"%0^=%2\\t// HImode RD^=RS\", xops);
  output_asm_insn (\"%1^=%3\", xops);
  return \"\";
}")

(define_insn "xorhi3_rri"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (xor:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "immediate_operand" "i")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP #IM16 */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  split_double (operands[2], &xops[4], &xops[5]);

  output_asm_insn (\"%0=%2^%4\\t// HImode RD=RS^#IMM16\", xops);
  output_asm_insn (\"%1=%3^%5\", xops);
  return \"\";
}")

(define_insn "xorhi3_rrQ"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (xor:HI (match_operand:HI 1 "register_operand" "r")
                (match_operand:HI 2 "direct16_memory_operand" "Q")))]
  ""
  "*
{
  /* Rd = Rs ALU_OP [#IM16] */

  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = adj_offsettable_operand (operands[2], 1);

  output_asm_insn (\"%0=%2^%4\\t// HImode RD=RS^[#IM16]\", xops);
  output_asm_insn (\"%1=%3^%5\", xops);
  return \"\";
}")

(define_insn "xorhi3_Qrr"
  [(set (match_operand:HI 0 "direct16_memory_operand" "=Q")
        (xor:HI (match_operand:HI 1 "register_operand" "r")
                 (match_operand:HI 2 "register_operand" "r")))]
  ""
  "*
{
  /* [#IM16] = Rd ALU_OP Rs */
  rtx xops[6];

  xops[0] = operands[0];
  xops[1] = adj_offsettable_operand (operands[0], 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = operands[2];
  xops[5] = gen_rtx_REG (QImode, REGNO (operands[2]) + 1);

  output_asm_insn (\"%0=%2^%4\\t// HImode [#IM16]=RD^RS\", xops);
  output_asm_insn (\"%1=%3^%5\", xops);
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_insn "mulqihi3"
  [(set (match_operand:HI 0 "register_operand" "=e")
        (mult:HI (sign_extend:HI (match_operand:QI 1 "register_operand" "h"))
                 (sign_extend:HI (match_operand:QI 2 "register_operand" "h"))))]
  ""
  "*
{
  return \"mr=%1*%2\\t// %0=%1*%2 32bit=16bit*16bit\";
}")

;===============================================================================

(define_insn "mulqi3_highpart"
  [(set (match_operand:QI 0 "register_operand" "=d")
        (truncate:QI (lshiftrt:HI (mult:HI (zero_extend:HI (match_operand:QI 1 "register_operand" "r"))
                                           (zero_extend:HI (match_operand:QI 2 "register_operand" "r")))
                                  (const_int 16))))
   (clobber (match_scratch:QI 3 "=c"))]
  ""
  "*
{
  return \"mr=%1*%2\\t// mulqi3_highpart: what we want is the higher 16bit in %0\";
}")

;===============================================================================
;===============================================================================

(define_expand "ashlqi3"
  [(set (match_operand:QI 0 "register_operand" "")
        (ashift:QI (match_operand:QI 1 "register_operand" "")
                   (match_operand:QI 2 "nonmemory_operand" "")))]
  ""
  "
{
  if (GET_CODE(operands[2]) == CONST)
    {
      emit_insn (gen_ashlqi3_rri (operands[0], operands[1], operands[2]));
      DONE;
    }
  else if (GET_CODE(operands[2]) == REG)
    {
      rtx ret;
      rtx insns;
      rtx equiv;

      start_sequence ();
      ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_lshiu1\"),
                                     NULL_RTX, 1, QImode, 2,
                                     operands[1], QImode,
                                     operands[2], QImode);
      equiv = gen_rtx (ASHIFT, QImode, operands[1], operands[2]);
      insns = get_insns ();
      end_sequence ();
      emit_libcall_block (insns, operands[0], ret, equiv);
      DONE;
    }
}")

(define_expand "ashlhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (ashift:HI (match_operand:HI 1 "register_operand" "")
                   (match_operand:QI 2 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_lshiu2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], QImode);
  equiv = gen_rtx (ASHIFT, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================

(define_insn "ashlqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ashift:QI (match_operand:QI 1 "register_operand" "r")
                   (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  int count, i, j;
  rtx xops[4];

  count = INTVAL (operands[2]) % BITS_PER_WORD;
  if (count < 0)
    count += BITS_PER_WORD;
  i = count / 4;
  j = count % 4;

  xops[0] = operands[0];
  xops[1] = operands[1];
  xops[2] = GEN_INT (j);
  xops[3] = GEN_INT (4);

  if (count == 0)
    return \"\";

  if (j != 0)
    output_asm_insn (\"%0=%1 lsl %2\", xops);
  else
    {
      output_asm_insn (\"%0=%1 lsl %3\", xops);
      if (i>0)
        i--;
    }

  while (i--)
    output_asm_insn (\"%0=%0 lsl %3\", xops);

  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "ashrqi3"
  [(set (match_operand:QI 0 "register_operand" "" )
        (ashiftrt:QI (match_operand:QI 1 "register_operand" "")
                     (match_operand:QI 2 "nonmemory_operand" "")))]
  ""
  "
{
  if (GET_CODE(operands[2]) == CONST)
    {
      emit_insn (gen_ashrqi3_rri (operands[0], operands[1], operands[2]));
      DONE;
    }
  else if (GET_CODE(operands[2]) == REG)
    {
      rtx ret;
      rtx insns;
      rtx equiv;

      start_sequence ();
      ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_rshi1\"),
                                     NULL_RTX, 1, QImode, 2,
                                     operands[1], QImode,
                                     operands[2], QImode);
      equiv = gen_rtx (ASHIFTRT, QImode, operands[1], operands[2]);
      insns = get_insns ();
      end_sequence ();
      emit_libcall_block (insns, operands[0], ret, equiv);

      DONE;
    }
}")

(define_expand "ashrhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (ashiftrt:HI (match_operand:HI 1 "register_operand" "")
                     (match_operand:QI 2 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_rshi2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], QImode);
  equiv = gen_rtx (ASHIFTRT, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================

(define_insn "ashrqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (ashiftrt:QI (match_operand:QI 1 "register_operand" "r")
                     (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  int count, i, j;
  rtx xops[4];

  count = INTVAL (operands[2]) % BITS_PER_WORD;
  if (count < 0)
    count += BITS_PER_WORD;
  i = count / 4;
  j = count % 4;

  xops[0] = operands[0];
  xops[1] = operands[1];
  xops[2] = GEN_INT(j);
  xops[3] = GEN_INT(4);

  if (count == 0)
    return \"\";

  if (j)
    output_asm_insn (\"%0=%1 asr %2\", xops);
  else
    {
      output_asm_insn (\"%0=%1 asr %3\", xops);
      if (i>0)
        i--;
    }

  while (i--)
    output_asm_insn (\"%0=%0 asr %3\", xops);

  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "lshrqi3"
  [(set (match_operand:QI 0 "register_operand" "" )
        (lshiftrt:QI (match_operand:QI 1 "register_operand" "")
                     (match_operand:QI 2 "nonmemory_operand" "")))]
  ""
  "
{
  if (GET_CODE(operands[2]) == CONST)
    {
      emit_insn (gen_lshrqi3_rri (operands[0], operands[1], operands[2]));
      DONE;
    }
  else /* if (GET_CODE(operands[2]) == REG) */
    {
      rtx ret;
      rtx insns;
      rtx equiv;

      start_sequence ();
      ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_rshu1\"),
                                     NULL_RTX, 1, QImode, 2,
                                     operands[1], QImode,
                                     operands[2], QImode);
      equiv = gen_rtx (LSHIFTRT, QImode, operands[1], operands[2]);
      insns = get_insns ();
      end_sequence ();
      emit_libcall_block (insns, operands[0], ret, equiv);
      DONE;
    }
}")

(define_expand "lshrhi3"
  [(set (match_operand:HI 0 "register_operand" "")
        (lshiftrt:HI (match_operand:HI 1 "register_operand" "")
                     (match_operand:QI 2 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_rshu2\"),
                                 NULL_RTX, 1, HImode, 2,
                                 operands[1], HImode,
                                 operands[2], QImode);
  equiv = gen_rtx (LSHIFTRT, HImode, operands[1], operands[2]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);

  DONE;
}")

;===============================================================================

(define_insn "lshrqi3_rri"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (lshiftrt:QI (match_operand:QI 1 "register_operand" "r")
                     (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  int count, i, j;
  rtx xops[4];

  count = INTVAL (operands[2]) % BITS_PER_WORD;
  if (count < 0)
    count += BITS_PER_WORD;
  i = count / 4;
  j = count % 4;

  xops[0] = operands[0];
  xops[1] = operands[1];
  xops[2] = GEN_INT (j);
  xops[3] = GEN_INT (4);

  if (count == 0)
    return \"\";

  if (j > 0)
    output_asm_insn (\"%0=%1 lsr %2\", xops);
  else
    {
      output_asm_insn (\"%0=%1 lsr %3\", xops);
      if (i > 0)
        --i;
    }

  while (i--)
    output_asm_insn (\"%0=%0 lsr %3\", xops);

  return \"\";
}")

;===============================================================================
;===============================================================================

(define_insn "rotlqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (rotate:QI (match_operand:QI 1 "register_operand" "r")
                   (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  int count, i, j;
  rtx xops[4];

  count = INTVAL (operands[2]) % BITS_PER_WORD;
  if (count < 0)
    count += BITS_PER_WORD;
  i = count / 4;
  j = count % 4;

  xops[0] = operands[0];
  xops[1] = operands[1];
  xops[2] = GEN_INT (j);
  xops[3] = GEN_INT (4);

  if (count == 0)
    return \"\";
  if (j > 0)
    output_asm_insn (\"%0=%1 rol %2\", xops);
  else
    ++i;
  while (i--)
    output_asm_insn (\"%0=%1 rol %3\", xops);
  return \"\";
}")

;===============================================================================

(define_insn "rotrqi3"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (rotatert:QI (match_operand:QI 1 "register_operand" "r")
                     (match_operand:QI 2 "immediate_operand" "i")))]
  ""
  "*
{
  int count, i, j;
  rtx xops[4];

  count = INTVAL (operands[2]) % BITS_PER_WORD;
  if (count < 0)
    count += BITS_PER_WORD;
  i = count / 4;
  j = count % 4;

  xops[0] = operands[0];
  xops[1] = operands[1];
  xops[2] = GEN_INT (j);
  xops[3] = GEN_INT (4);

  if (count == 0)
    return \"\";
  if (j > 0)
    output_asm_insn (\"%0=%1 ror %2\", xops);
  else
    ++i;
  while (i--)
    output_asm_insn(\"%0=%1 ror %3\", xops);
  return \"\";
}")

;===============================================================================

(define_expand "negqi2"
  [(set (match_operand:QI 0 "register_operand" "")
        (neg:QI (match_operand:QI 1 "general_operand" "" )))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "neghi2"
  [(set (match_operand:HI 0 "register_operand" "")
        (neg:HI (match_operand:HI 1 "nonregister_operand" "")))]
  ""
  "
{
  if (GET_CODE (operands[2]) == REG)
    FAIL;

  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  emit_insn (gen_movhi_ri (operands[0], const0_rtx));

  if (GET_CODE (operands[1]) == CONST_INT)
    {
      emit_insn (gen_subhi3_rri (operands[0], operands[0], operands[1]));
    }
  else
    {
      if (direct16_memory_operand (operands[1], HImode))
        {
          emit_insn (gen_subhi3_rrQ (operands[0], operands[0], operands[1]));
        }
      else
        {
          emit_insn (gen_subhi3_r0all (operands[0], operands[0], operands[1]));
        }
    }
  DONE;
}")

(define_expand "neghf2"
  [(set (match_operand:HF 0 "register_operand" "")
        (neg:HF (match_operand:HF 1 "register_operand" "")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_negf2\"),
                                 NULL_RTX, 1, HFmode, 1,
                                 operands[1], HFmode);
  equiv = gen_rtx (NEG, HFmode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================

(define_insn "negqi2_all"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (neg:QI (match_operand:QI 1 "general_operand" "rim")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM
      && GET_CODE (XEXP (operands[1], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
      && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 64)
    {
      int i;
      int j;
      rtx xops[4];

      i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[1], 0), 0)));
      xops[1] = GEN_INT (i);
      xops[2] = gen_rtx_MEM (QImode, gen_rtx (PLUS, QImode,
                                              xops[0], GEN_INT (j)));
      xops[3] = operands[0];

      output_asm_insn (\"%0=%0+%1\", xops);
      output_asm_insn (\"%3=-%2\", xops);
      output_asm_insn (\"%0=%0-%1\", xops);
    }
  else
    {
      output_asm_insn (\"%0=-%1\\t// QImode negative\", operands);
    }
  return \"\";
}")

;(define_insn "neghi2_all"
;  [(set (match_operand:HI 0 "register_operand" "=r")
;        (neg:HI (match_operand:HI 1 "general_operand" "rim")))]
;  ""
;  "*
;{
;  emit_insn (gen_movhi_ri (operands[0], const0_rtx));
;
;  if (GET_CODE (operands[1]) == REG)
;    {
;      emit_insn (gen_subhi3_r0r (operands[0], operands[1]));
;    }
;  else if (GET_CODE (operands[1]) == CONST_INT)
;    {
;      emit_insn (gen_subhi3_rri (operands[0], operands[0], operands[1]));
;    }
;  else
;    {
;      if (direct16_memory_operand (operands[1], HImode))
;        {
;          emit_insn (gen_subhi3_rrQ (operands[0], operands[0], operands[1]));
;        }
;      else
;        {
;          emit_insn (gen_subhi3_r0R (operands[0], operands[0], operands[1]));
;        }
;    }
;  return \"\";
;}")

;===============================================================================

(define_insn "one_cmplqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (not:QI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "%0=%1^0xffff\\t// one_cmplqi2")

(define_insn "one_cmplhi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (not:HI (match_operand:HI 1 "register_operand" "r")))]
  ""
  "*
{
  rtx xops[5];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];
  xops[3] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);
  xops[4] = GEN_INT (0xffff);
  output_asm_insn (\"%0=%2^%4\\t// one_cmplhi2\", xops);
  output_asm_insn (\"%1=%3^%4\", xops);
  return \"\";
}")

;===============================================================================

(define_expand "cmpqi"
  [(set (cc0)
        (compare (match_operand:QI 0 "register_operand" "")
                 (match_operand:QI 1 "general_operand" "")))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "cmphi"
  [(set (cc0)
        (compare (match_operand:HI 0 "register_operand" "")
                 (match_operand:HI 1 "nonmemory_operand" "")))]
  ""
  "
{
}")

(define_expand "cmphf"
  [(set (cc0)
        (compare (match_operand:HF 0 "register_operand" "")
                 (match_operand:HF 1 "register_operand" "")))]
  ""
  "
{
  unsp_compare_mode = HFmode;

  emit_library_call (gen_rtx (SYMBOL_REF, Pmode, \"_cmpf2\"),
                     1, QImode, 2,
                     operands[0], HFmode,
                     operands[1], HFmode);
  /* The __cmpf2(A,B) returns 2: if A>B, 1: if A==B, 0: if A<B */
  emit_insn (gen_cmpqi_all (copy_to_reg (hard_libcall_value (QImode)),
                            GEN_INT (1)));
  DONE;
}")

;===============================================================================

(define_insn "cmpqi_all"
  [(set (cc0)
        (compare (match_operand:QI 0 "register_operand" "r")
                 (match_operand:QI 1 "general_operand" "rim")))]
  ""
  "*
{
  unsp_compare_mode = QImode;

  if (GET_CODE (operands[1]) == SYMBOL_REF
      && far_ptr_name (XSTR (operands[1], 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[2];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (operands[1], 0));
      xops[0] = operands[0];
      xops[1] = gen_rtx_SYMBOL_REF (QImode, name);
      output_asm_insn (\"CMP %0,%1\\t// QImode compare\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[1]) == CONST
           && GET_CODE (XEXP (operands[1], 0)) == PLUS
           && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == SYMBOL_REF
           && far_ptr_name (XSTR (XEXP (XEXP (operands[1], 0), 0), 0)) == 1)
    {
      /* Special handle for function pointer */
      rtx xops[2];
      char name[60];

      sprintf (name, \"*%s_entry\", XSTR (XEXP (XEXP (operands[2], 0), 0), 0));
      xops[0] = operands[0];
      xops[1] = gen_rtx (CONST, QImode, gen_rtx (PLUS, QImode, gen_rtx_SYMBOL_REF (QImode, name), XEXP (XEXP (operands[1], 0), 1)));
      output_asm_insn (\"CMP %0,%1\\t// QImode compare\", xops);
      return \"\";
    }


  return \"CMP %0,%1\\t// QImode compare\";
}")

(define_insn "cmphi_all"
  [(set (cc0)
        (compare (match_operand:HI 0 "register_operand" "r")
                 (match_operand:HI 1 "general_operand" "rim")))]
  ""
  "*
{
  rtx xops[6];

  unsp_compare_mode = HImode;
  unsp_compare_op0 = operands[0];

  /* Emit high part compare here */
  if (GET_CODE (operands[1]) == CONST_INT)
    {
      xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
      split_double (operands[1], &unsp_compare_op1, &xops[1]);

      output_asm_insn (\"CMP %0,%1\\t// HImode compare\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[1]) == REG)
    {
      unsp_compare_op1 = operands[1]; /* The low part */

      xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
      xops[1] = gen_rtx_REG (QImode, REGNO (operands[1]) + 1);

      output_asm_insn (\"CMP %0,%1\\t// HImode compare\", xops);
      return \"\";
    }
  else if (GET_CODE (operands[1]) == MEM)
    {
      if (GET_CODE (XEXP (operands[1], 0)) == PRE_INC)
        {
          /* CMP R1,[++R4] => R4+=3; CMP R2,[R4--]; CMP R1,[R4]; */
          xops[0] = XEXP (XEXP (operands[1], 0), 0);
          xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (XEXP (operands[1], 0), 0)));
                                          
          unsp_compare_op1 = gen_rtx_MEM (QImode, 
                                          XEXP (XEXP (operands[1], 0), 0));
          
          output_asm_insn (\"%0=%0+3\\t// CMP RD,[++RS] HImode\", xops);
          output_asm_insn (\"CMP %1,%2\", xops);
          return \"\";
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == POST_INC)
        {
          /* CMP R1,[R4++] => R4+=1; CMP R2,[R4--]; CMP R1,[R4++]; */
          debug_rtx (operands[0]);
          debug_rtx (operands[1]);
          
          abort ();
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == POST_DEC)
        {
          /* CMP R1,[R4--] => ?? */
          debug_rtx (operands[0]);
          debug_rtx (operands[1]);
          
          abort ();
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == REG)
        {
          /* CMP R1,[R4] => R4+=1; CMP R2,[R4--]; CMP R1,[R4]; */
          xops[0] = XEXP (operands[1], 0);
          xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
          xops[2] = gen_rtx_MEM (QImode,
                                 gen_rtx (POST_DEC, QImode, 
                                          XEXP (operands[1], 0)));
                                          
          unsp_compare_op1 = gen_rtx_MEM (QImode, 
                                          XEXP (operands[1], 0));
          
          output_asm_insn (\"%0=%0+1\\t// CMP RD,[RS] HImode\", xops);
          output_asm_insn (\"CMP %1,%2\", xops);
          return \"\";
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == PLUS
               && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
               && REG_OK_FOR_BASE_P (XEXP (XEXP (operands[1], 0), 0))
               && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 0
               && INTVAL (XEXP (XEXP (operands[1], 0), 1)) <= 62)
        {
          xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
          xops[1] = gen_rtx_MEM (QImode,
                                 gen_rtx (PLUS, QImode,
                                          XEXP (XEXP (operands[1], 0), 0),
                                          GEN_INT (INTVAL (XEXP (XEXP (operands[1], 0), 1)) + 1)));

          unsp_compare_op1 = operands[1];
    
          output_asm_insn (\"CMP %0,%1\\t// CMP RD,[RS] HImode\", xops);
          return \"\";
        }
      else if (offsettable_memref_p (operands[1]))
        {
          unsp_compare_op1 = operands[1];

          xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
          xops[1] = adj_offsettable_operand (operands[1], 1);
    
          output_asm_insn (\"CMP %0,%1\\t// CMP RD,[Label] HImode\", xops);
          return \"\";
        }
      else
        {
          debug_rtx (operands[0]);
          debug_rtx (operands[1]);

          abort ();
        }
    }
  else
    {
      debug_rtx (operands[0]);
      debug_rtx (operands[1]);

      abort ();
    }
}");

;===============================================================================

(define_expand "tstqi"
  [(set (cc0)
        (match_operand:QI 0 "register_operand" ""))]
  ""
  "
{
}")

(define_expand "tsthi"
  [(set (cc0)
        (match_operand:HI 0 "register_operand" ""))]
  ""
  "
{
}")

;===============================================================================

(define_insn "tstqi_all"
  [(set (cc0)
        (match_operand:QI 0 "register_operand" "r"))]
  ""
  "*
{
  unsp_compare_mode = QImode;
  return \"CMP %0,0\\t// QImode test\";
}")

(define_insn "tsthi_all"
  [(set (cc0)
        (match_operand:HI 0 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[1];

  unsp_compare_mode = HImode;
  unsp_compare_op0 = operands[0];
  unsp_compare_op1 = GEN_INT (0);

  xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

  output_asm_insn (\"CMP %0,0\\t// HImode test\", xops);
  return \"\";
}")

;===============================================================================

(define_expand "floatqihf2"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (float:HF (match_operand:QI 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvi1f2\"),
                                 NULL_RTX, 1, HFmode, 1,
                                 operands[1], QImode);
  equiv = gen_rtx (FLOAT, HFmode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "floathihf2"
  [(set (match_operand:HF 0 "register_operand" "=r")
        (float:HF (match_operand:HI 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvi2f2\"),
                                 NULL_RTX, 1, HFmode, 1,
                                 operands[1], HImode);
  equiv = gen_rtx (FLOAT, HFmode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================

(define_expand "fix_trunchfqi2"
  [( set (match_operand:QI 0 "register_operand" "=r")
         (fix:QI (match_operand:HF 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvf2i1\"),
                                 NULL_RTX, 1, QImode, 1,
                                 operands[1], HFmode);
  equiv = gen_rtx (FIX, QImode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "fix_trunchfhi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (fix:HI (match_operand:HF 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvf2i2\"),
                                 NULL_RTX, 1, HImode, 1,
                                 operands[1], HFmode);
  equiv = gen_rtx (FIX, HImode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================

(define_expand "fixuns_trunchfqi2"
  [( set (match_operand:QI 0 "register_operand" "=r")
         (fix:QI (match_operand:HF 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvf2i1\"),
                                 NULL_RTX, 1, QImode, 1,
                                 operands[1], HFmode);
  equiv = gen_rtx (FIX, QImode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

(define_expand "fixuns_trunchfhi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (fix:HI (match_operand:HF 1 "register_operand" "r")))]
  ""
  "
{
  rtx ret;
  rtx insns;
  rtx equiv;

  start_sequence ();
  ret = emit_library_call_value (gen_rtx (SYMBOL_REF, Pmode, \"_cvf2i2\"),
                                 NULL_RTX, 1, HImode, 1,
                                 operands[1], HFmode);
  equiv = gen_rtx (FIX, HImode, operands[1]);
  insns = get_insns ();
  end_sequence ();
  emit_libcall_block (insns, operands[0], ret, equiv);
  DONE;
}")

;===============================================================================

(define_insn "trunchiqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (truncate:QI (match_operand:HI 1 "nonimmediate_operand" "rm" )))]
  ""
  "*
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  return \"%0=%1\\t// trunchiqi2\" ;
}")

;===============================================================================

(define_expand "extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "")
        (sign_extend:HI (match_operand:QI 1 "nonimmediate_operand" "")))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

;===============================================================================

(define_insn "extendqihi2_all"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (sign_extend:HI (match_operand:QI 1 "nonimmediate_operand" "rm")))]
 ""
 "*
{
  rtx xops[3];

  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];

  if (GET_CODE (operands[1]) == REG)
    {
      if ((REGNO (operands[0]) + 1) == REGNO (operands[1]))
        {
          output_asm_insn (\"%0=%2\\t// sign extend\", xops);
          output_asm_insn (\"%1=0\", xops);
          output_asm_insn (\"%0=%0\", xops);
          output_asm_insn (\"jpl 1\", xops);
          output_asm_insn (\"%1=-1\", xops);
          return \"\";
        }
      else
        {
          output_asm_insn (\"%1=0\\t// sign extend\", xops);
          output_asm_insn (\"%0=%2\", xops);
          output_asm_insn (\"jpl 1\", xops);
          output_asm_insn (\"%1=-1\", xops);
          return \"\";
        }
    }
  else
    {
      if (GET_CODE (XEXP (operands[1], 0)) == PLUS
          && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
          && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
          && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 64)
        {
          int i;
          int j;
          rtx xxops[3];

          i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
          j = i % 64;
          i = i - j;

          xxops[0] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[1], 0), 0)));
          xxops[1] = GEN_INT (i);
          xxops[2] = gen_rtx_MEM (QImode, gen_rtx (PLUS, QImode,
                                                   xxops[0], GEN_INT (j)));


          output_asm_insn (\"%0=%0+%1\", xxops);
          xops[2] = xxops[2];
          {
            output_asm_insn (\"%1=0\\t// sign extend\", xops);
            output_asm_insn (\"%0=%2\", xops);
            output_asm_insn (\"jpl 1\", xops);
            output_asm_insn (\"%1=-1\", xops);
          }
          output_asm_insn (\"%0=%0-%1\", xxops);
          return \"\";
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == PRE_INC
               || GET_CODE (XEXP (operands[1], 0)) == POST_INC
               || GET_CODE (XEXP (operands[1], 0)) == POST_DEC)
        {
          if (REGNO (operands[0]) + 1 == REGNO (XEXP (XEXP (operands[1], 0), 0)))
            {
              output_asm_insn (\"%0=%2\\t// sign extend\", xops);
              output_asm_insn (\"jpl 2\", xops);
              output_asm_insn (\"%1=-1\", xops);
              output_asm_insn (\"jmp 1\", xops);
              output_asm_insn (\"%1=0\", xops);
            }
          else
            {
              output_asm_insn (\"%1=0\\t// sign extend\", xops);
              output_asm_insn (\"%0=%2\", xops);
              output_asm_insn (\"jpl 1\", xops);
              output_asm_insn (\"%1=-1\", xops);
            }
          return \"\";
        }
      else if (GET_CODE (XEXP (operands[1], 0)) == REG)
        {
          if (REGNO (operands[0]) + 1 == REGNO (XEXP (operands[1], 0)))
            {
              output_asm_insn (\"%0=%2\\t// sign extend\", xops);
              output_asm_insn (\"jpl 2\", xops);
              output_asm_insn (\"%1=-1\", xops);
              output_asm_insn (\"jmp 1\", xops);
              output_asm_insn (\"%1=0\", xops);
            }
          else
            {
              output_asm_insn (\"%1=0\\t// sign extend\", xops);
              output_asm_insn (\"%0=%2\", xops);
              output_asm_insn (\"jpl 1\", xops);
              output_asm_insn (\"%1=-1\", xops);
            }
          return \"\";
        }
      output_asm_insn (\"%1=0\\t// sign extend\", xops);
      output_asm_insn (\"%0=%2\", xops);
      output_asm_insn (\"jpl 1\", xops);
      output_asm_insn (\"%1=-1\", xops);
      return \"\";
    }
}")

;===============================================================================
;===============================================================================

(define_expand "zero_extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "")
        (zero_extend:HI (match_operand:QI 1 "nonimmediate_operand" "")))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

;===============================================================================

(define_insn "zero_extendqihi2_all"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (zero_extend:HI (match_operand:QI 1 "nonimmediate_operand" "rm")))]
  ""
  "*
{
  rtx xops[5];

  if (GET_CODE (operands[1]) == REG
      && REGNO (operands[0]) == REGNO (operands[1]))
    {
      xops[0] = operands[0];
      xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
      xops[2] = operands[1];

      output_asm_insn(\"%1=0\\t// zero extend %0=%2\", xops);
      return \"\";
    }
  if (GET_CODE (operands[1]) == MEM
      && GET_CODE (XEXP (operands[1], 0)) == PLUS
      && GET_CODE (XEXP (XEXP (operands[1], 0), 0)) == REG
      && REG_OK_FOR_BASE_P (XEXP ( XEXP (operands[1], 0), 0))
      && INTVAL (XEXP (XEXP (operands[1], 0), 1)) >= 64)
    {
      int i;
      int j;

      i = INTVAL (XEXP (XEXP (operands[1], 0), 1));
      j = i % 64;
      i = i - j;

      xops[0] = gen_rtx_REG (QImode, REGNO (XEXP (XEXP (operands[1], 0), 0)));
      xops[1] = GEN_INT (i);
      xops[2] = gen_rtx_MEM (QImode, gen_rtx (PLUS, QImode,
                                              xops[0], GEN_INT (j)));
      xops[3] = gen_rtx_REG (QImode, REGNO (operands[0]));
      xops[4] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);

      output_asm_insn (\"%0+=%1\\t// zero_extendqihi_all\", xops);
      output_asm_insn (\"%3=%2\", xops);
      output_asm_insn (\"%4=0\", xops);
      output_asm_insn (\"%0-=%1\", xops);
      return \"\";
    }

  xops[0] = gen_rtx_REG (QImode, REGNO (operands[0]));
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  xops[2] = operands[1];

  output_asm_insn (\"%0=%2\", xops);
  output_asm_insn (\"%1=0\", xops);

  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "beq"
  [(set (pc)
        (if_then_else (eq (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bne"
  [(set (pc)
        (if_then_else (ne (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bgt"
  [(set (pc)
        (if_then_else (gt (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bgtu"
  [(set (pc)
        (if_then_else (gtu (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "blt"
  [(set (pc)
        (if_then_else (lt (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bltu"
  [(set (pc)
        (if_then_else (ltu (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bge"
  [(set (pc)
        (if_then_else (ge (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bgeu"
  [(set (pc)
        (if_then_else (geu (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "ble"
  [(set (pc)
        (if_then_else (le (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

(define_expand "bleu"
  [(set (pc)
        (if_then_else (leu (cc0) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }
}")

;===============================================================================

(define_insn "branch_all"
  [(set (pc)
        (if_then_else (match_operator 0 "comparison_operator" [(cc0) (const_int 0)])
                      (label_ref (match_operand 1 "" ""))
                      (pc)))]
  ""
  "*
{
  gen_compare_branch(operands[0], operands[1]);
  return \"\";
}")

;===============================================================================

(define_expand "call"
  [(call (match_operand:QI 0 "" "")
         (match_operand:QI 1 "" ""))]
  ""
  "
{
  if (GET_CODE (operands[0]) == MEM
      && ! call_address_operand (XEXP (operands[0], 0), QImode))
    operands[0] = gen_rtx (MEM, GET_MODE (operands[0]),
                           force_reg (Pmode, XEXP (operands[0], 0)));
}")

(define_expand "call_value"
  [(set (match_operand 0 "register_operand" "=r")
        (call (match_operand:QI 1 "" "")
              (match_operand:QI 2 "" "")))]
  ""
  "
{
  if (GET_CODE (operands[1]) == MEM
      && ! call_address_operand (XEXP (operands[1], 0), QImode))
    operands[1] = gen_rtx (MEM, GET_MODE (operands[1]),
                           force_reg (Pmode, XEXP (operands[1], 0)));
}")

;(define_expand "untyped_call"
;  [(parallel [(call (match_operand 0 "call_address_operand" "R") (const_int 0))
;              (match_operand 1 "" "")
;              (match_operand 2 "" "")])]
;  ""
;  "
;{
;  int i;
;
;  emit_call_insn (gen_call (operands[0], const0_rtx, NULL, const0_rtx));
;
;  for (i = 0; i < XVECLEN (operands[2], 0); i++)
;    {
;      rtx set = XVECEXP (operands[2], 0, i);
;      emit_move_insn (SET_DEST (set), SET_SRC (set));
;    }
;
;  /* The optimizer does not know that the call sets the function value
;     registers we stored in the result block.  We avoid problems by
;     claiming that all hard registers are used and clobbered at this
;     point.  */
;  emit_insn (gen_blockage ());
;
;  DONE;
;}")

;===============================================================================

(define_insn "call_1"
  [(call (mem:QI (match_operand:QI 0 "call_address_operand" ""))
         (match_operand 1 "" ""))]
  ""
  "*
{
  return \"call %0\\t// call without return value\" ;
}")

(define_insn "call_2"
  [(call (mem:QI (match_operand:QI 0 "register_operand" "r"))
         (match_operand 1 "" ""))]
  ""
  "*
{
  rtx xops[3];
  int i;

  xops[0] = operands[0];

  /* Find a temp register other than operands[1] */
  i = REGNO (operands[0]) + 1;
  if (i > REG_R4)
    i = REG_R1;
  xops[1] = gen_rtx_REG (QImode, i);
  xops[2] = gen_rtx_LABEL_REF (QImode, gen_label_rtx ());

  output_asm_insn (\"//call function by pointer without return value\", xops);
  output_asm_insn (\"%0-=1\", xops);
  /*
  output_asm_insn (\"%1=PC+4\", xops);
  */
  output_asm_insn (\"%1=%2\", xops);
  output_asm_insn (\"push %1 to [SP]\", xops);
  output_asm_insn (\"push SR to [SP]\", xops);
  output_asm_insn (\"pop SR, PC from [%0]\", xops);
  output_asm_insn (\"//end of expand\\n%2:\", xops);

  /* Original version which all pointer is NEAR */
/*
  output_asm_insn (\"//call function by pointer without return value\", xops);
  output_asm_insn (\"%1=PC+4\", xops);
  output_asm_insn (\"push %1 to [SP]\", xops);
  output_asm_insn (\"push SR to [SP]\", xops);
  output_asm_insn (\"PC=%0\", xops);
  output_asm_insn (\"//end of expand\", xops);
*/

  return \"\";
}")

(define_insn "call_value_1"
  [(set (match_operand 0 "register_operand" "=r")
        (call (mem:QI (match_operand:QI 1 "call_address_operand" ""))
              (match_operand:QI 2 "" "")))]
  ""
  "*
{
  return \"call %1\\t// call with return value\" ;
}")

(define_insn "call_value_2"
  [(set (match_operand 0 "register_operand" "=r")
        (call (mem:QI (match_operand:QI 1 "register_operand" "r"))
              (match_operand:QI 2 "" "")))]
  ""
  "*
{
  rtx xops[3];
  int i;

  xops[0] = operands[1];

  /* Find a temp register other than operands[1] */
  i = REGNO (operands[1]) + 1;
  if (i > REG_R4)
    i = REG_R1;
  xops[1] = gen_rtx_REG (QImode, i);
  xops[2] = gen_rtx_LABEL_REF (QImode, gen_label_rtx ());

  output_asm_insn (\"//call function by pointer with return value\", xops);
  output_asm_insn (\"%0-=1\", xops);
  /*
  output_asm_insn (\"%1=pc+4\", xops);
  */
  output_asm_insn (\"%1=%2\", xops);
  output_asm_insn (\"push %1 to [SP]\", xops);
  output_asm_insn (\"push SR to [SP]\", xops);
  output_asm_insn (\"pop SR, PC from [%0]\\n%2:\", xops);

  /* Original version which all pointer is NEAR */
/*
  output_asm_insn (\"//call function by pointer with return value\", xops);
  output_asm_insn (\"%1=pc+3\", xops);
  output_asm_insn (\"push %1 to [sp]\", xops);
  output_asm_insn (\"push SR to [sp]\", xops);
  output_asm_insn (\"pc=%0\", xops);
*/
  return \"\";
}")

;===============================================================================
;===============================================================================

(define_expand "allocate_stack"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (minus:QI (reg:QI 0) (match_operand:QI 1 "general_operand" "")))
   (set (reg:QI 0) (minus:QI (reg:QI 0) (match_dup 1)))]
  ""
  "
{
  if (TARGET_WARN_SEC_VAR)
    {
      char * var_name;
      char * sec_name;
      extern char * check_sec_var(rtx, char **, char **);

      if (check_sec_var (operands[0], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
      if (check_sec_var (operands[1], &var_name, &sec_name))
        warning (\"using variable \\\"%s\\\" in \\\"%s\\\" section.\", var_name, sec_name);
    }

  emit_insn (gen_subqi3 (stack_pointer_rtx, stack_pointer_rtx, operands[1]));
  emit_insn (gen_addqi3 (operands[0], stack_pointer_rtx, const1_rtx));
  DONE;
}")

;===============================================================================
;===============================================================================

(define_insn "blockage"
  [(unspec_volatile [(const_int 0)] 0)]
  ""
  "")

;===============================================================================

(define_insn "nop"
  [(const_int 0)]
  ""
  "nop")

;===============================================================================

(define_insn "indirect_jump"
  [(set (pc)
        (match_operand:QI 0 "general_operand" ""))]
  ""
  "pc=%0\\t// Indirect jump")

;===============================================================================

(define_insn "tablejump"
  [(set (pc) (match_operand:QI 0 "nonimmediate_operand" "rm"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "*
{
  return \"pc=%0\\t// tablejump\";
}")

;===============================================================================

(define_insn "jump"
  [(set (pc)
        (label_ref (match_operand 0 "" "")))]
  ""
  "pc=%0\\t// jump")

;===============================================================================

(define_insn ""
  [(set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 0 "register_operand" "r"))
   (set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 1 "register_operand" "r"))]
  "((REGNO (operands[0]) - REGNO (operands[1])) == 2)"
  "push r1,r4 to [sp]")

(define_insn ""
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 1 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 2 "register_operand" "r"))]
  "((REGNO (operands[0]) - REGNO (operands[1])) == 1
    && (REGNO (operands[1]) - REGNO (operands[2])) == 1)"
  "push %2,%0 to [sp]")

(define_insn ""
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 1 "register_operand" "r"))]
  "((REGNO (operands[0]) - REGNO (operands[1])) == 1)"
  "push %1,%0 to [sp]")

;===============================================================================

(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 2 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 3 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO (operands[1]) - REGNO (operands[0])) == 1
    && (REGNO (operands[2]) - REGNO (operands[1])) == 1
    && (REGNO (operands[3]) - REGNO (operands[2])) == 1)"
  "pop %0,%3 from [sp]")

(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 2 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO (operands[1]) - REGNO (operands[0])) == 1
    && (REGNO (operands[2]) - REGNO (operands[1])) == 1)"
  "pop %0,%2 from [sp]")

(define_insn ""
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "=r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO (operands[1]) - REGNO (operands[0])) == 1)"
  "pop %0,%1 from [sp]")

;===============================================================================

(define_insn "pushqi"
  [(set (mem:QI (post_dec:QI (match_operand:QI 0 "register_operand" "r")))
        (match_operand:QI 1 "register_operand" "r"))]
  "REGNO (operands[1]) != REGNO (operands[0])"
  "push %1 to [%0]\\t// pushqi")

(define_insn "pushhi"
  [(set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 0 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[2];
  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  output_asm_insn (\"push %0,%1 to [sp]\\t// pushhi\", xops);
  return \"\";
}")

(define_insn "pushhf"
  [(set (mem:HF (post_dec:QI (reg:QI 0)))
        (match_operand:HF 0 "register_operand" "r"))]
  ""
  "*
{
  rtx xops[2];
  xops[0] = operands[0];
  xops[1] = gen_rtx_REG (QImode, REGNO (operands[0]) + 1);
  output_asm_insn (\"push %0,%1 to [sp]\\t// pushhf\", xops);
  return \"\";
}")

;===============================================================================

(define_insn "popqi"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (mem:QI (pre_inc:QI (match_operand:QI 1 "register_operand" "r"))))]
  "REGNO (operands[1]) != REGNO (operands[0])"
  "pop %0 from [%1]\\t// popqi")

(define_insn "pophi"
  [(set (match_operand:HI 0 "register_operand" "=r")
        (mem:HI (pre_inc:QI (reg:QI 0))))]
  "REGNO (operands[0]) >= 1 && REGNO (operands[0]) <= 4"
  "*
{
  if (REGNO (operands[0]) == 1)
    return \"pop r1,r2 from [sp]\\t// pophi\";
  if (REGNO (operands[0]) == 2)
    return \"pop r2,r3 from [sp]\\t// pophi\";
  if (REGNO (operands[0]) == 3)
    return \"pop r3,r4 from [sp]\\t// pophi\";
  if (REGNO (operands[0]) == 4)
    return \"pop r4,bp from [sp]\\t// pophi\";
}")

;===============================================================================

(define_insn ""
  [(set (reg:QI 0)
        (plus:QI (reg:QI 0)
                 (match_operand:QI 0 "immediate_operand" "i")))]
  ""
  "sp+=%0\\t// sp+imm")

;===============================================================================

;(define_insn ""
;  [(set (cc0)
;        (and:QI (match_operand:QI 0 "register_operand" "%r")
;                (match_operand:QI 1 "general_operand" "rim")))]
;  ""
;  "test %0,%1")

;===============================================================================
; Split
;===============================================================================

;(define_split
;  [(set (match_operand:QI 0 "register_operand" "")
;        (minus:QI (match_operand:QI 1 "register_operand" "")
;                  (match_operand:QI 2 "register_operand" "")))]
;  ""
;  [(set (match_dup 0)
;        (match_dup 1))
;   (set (match_dup 0)
;        (minus:QI (match_dup 0)
;                  (match_dup 2)))]
;  "
;{
;}")

;===============================================================================
; Peephole optimizations
;===============================================================================

(define_peephole
  [(set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 0 "register_operand" "r"))
   (set (mem:HI (post_dec:QI (reg:QI 0 )))
        (match_operand:HI 1 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 2)"
  "push r1,r4 to [sp]\\t// peepholes qi2_si")

(define_peephole
  [(set (mem:HF (post_dec:QI (reg:QI 0)))
        (match_operand:HF 0 "register_operand" "r"))
   (set (mem:HF (post_dec:QI (reg:QI 0 )))
        (match_operand:HF 1 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 2)"
  "push r1,r4 to [sp]\\t// peepholes qi2_si")

(define_peephole
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 1 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 2 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0 )))
        (match_operand:QI 3 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 1 &&
    (REGNO(operands[1]) - REGNO(operands[2])) == 1 &&
    (REGNO(operands[2]) - REGNO(operands[3])) == 1)"
  "push %3,%0 to [sp]\\t// peephole pushqi4")

(define_peephole
  [(set (match_operand:QI 0 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 2 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 3 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO(operands[1]) - REGNO(operands[0])) == 1 &&
    (REGNO(operands[2]) - REGNO(operands[1])) == 1 &&
    (REGNO(operands[3]) - REGNO(operands[2])) == 1)"
  "pop %0,%3 from [sp]\\t// peephole popqi4")

(define_peephole
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 1 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 2 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 1 &&
    (REGNO(operands[1]) - REGNO(operands[2])) == 1)"
  "push %2,%0 to [sp]\\t// peephole pushqi3")

(define_peephole
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 1 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 2)"
  "push %1,%0 to [sp]\\t// peephole qi1_hi1")

(define_peephole
  [(set (mem:HI (post_dec:QI (reg:QI 0)))
        (match_operand:HI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 1 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 1)"
  "*
{
  operands[2]=gen_rtx_REG(QImode, REGNO(operands[0]) + 1);
  return \"push %1,%2 to [sp]\\t// peephole hi1_qi1\";
}")

(define_peephole
  [(set (match_operand:QI 0 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 2 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO(operands[1]) - REGNO(operands[0])) == 1 &&
    (REGNO(operands[2]) - REGNO(operands[1])) == 1)"
  "pop %0,%2 from [sp]\\t// peephole popqi3")

(define_peephole
  [(set (mem:QI (post_dec:QI (reg:QI 0)))
        (match_operand:QI 0 "register_operand" "r"))
   (set (mem:QI (post_dec:QI (reg:QI 0 )))
        (match_operand:QI 1 "register_operand" "r"))]
  "((REGNO(operands[0]) - REGNO(operands[1])) == 1)"
  "push %1,%0 to [sp]\\t// peepholes pushqi2")

(define_peephole
  [(set (match_operand:QI 0 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))
   (set (match_operand:QI 1 "register_operand" "r")
        (mem:QI (pre_inc:QI (reg:QI 0))))]
  "((REGNO(operands[1]) - REGNO(operands[0])) == 1)"
  "pop %0,%1 from [sp]\\t// peepholes popqi2")

;===============================================================================

(define_peephole
  [(set (reg:QI 5)
        (minus:QI (reg:QI 5)
                  (match_operand:QI 0 "immediate_operand" "i")))
   (set (reg:QI 5)
        (plus:QI (reg:QI 5)
                 (match_operand:QI 1 "immediate_operand" "i")))]
  "(INTVAL(operands[0]) == INTVAL(operands[1]))"
  "// BP-=%0,BP+=%1 eliminated")

(define_peephole
  [(set (reg:QI 5)
        (minus:QI (reg:QI 5)
                  (match_operand:QI 0 "immediate_operand" "i")))
   (set (reg:QI 5)
        (plus:QI (reg:QI 5)
                 (match_operand:QI 1 "immediate_operand" "i")))]
  "(INTVAL(operands[0]) != INTVAL(operands[1]))"
  "BP=BP-%0+%1\\t// derive from BP-=%0,BP+=%1")
