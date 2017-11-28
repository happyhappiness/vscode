                 PARSE_ERROR;
             }
             Var->val_len = sizeof(int);
             bufp = asn_parse_int(DataPtr, &ThisVarLen,
                                  &Var->type, (int *) Var->val.integer,
                                  Var->val_len);
-#ifdef DEBUG_VARS_DECODE
+#if DEBUG_VARS_DECODE
             printf("VARS: Decoded integer '%d' (%d bytes left)\n",
                    *(Var->val.integer), ThisVarLen);
 #endif
             break;
 
         case SMI_COUNTER32:
