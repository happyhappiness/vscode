                 PARSE_ERROR;
             }
             Var->val_len = sizeof(u_int);
             bufp = asn_parse_unsigned_int(DataPtr, &ThisVarLen,
                                           &Var->type, (u_int *) Var->val.integer,
                                           Var->val_len);
-#ifdef DEBUG_VARS_DECODE
+#if DEBUG_VARS_DECODE
             printf("VARS: Decoded timeticks '%d' (%d bytes left)\n",
                    *(Var->val.integer), ThisVarLen);
 #endif
             break;
 
         case ASN_OCTET_STR:
