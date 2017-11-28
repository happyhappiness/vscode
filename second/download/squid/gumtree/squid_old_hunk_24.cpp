                snmp_set_api_error(SNMPERR_OS_ERR);
                PARSE_ERROR;
            }
            bufp = asn_parse_string(DataPtr, &ThisVarLen,
                                    &Var->type, Var->val.string,
                                    &Var->val_len);
#ifdef DEBUG_VARS_DECODE
            printf("VARS: Decoded string '%s' (length %d) (%d bytes left)\n",
                   (Var->val.string), Var->val_len, ThisVarLen);
#endif
            break;

        case ASN_OBJECT_ID:
