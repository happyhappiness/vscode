            if (Var->val.integer == NULL) {
                snmp_set_api_error(SNMPERR_OS_ERR);
                PARSE_ERROR;
            }
            /* Only copy if we successfully decoded something */
            if (bufp) {
                memcpy((char *) Var->val.objid, (char *) TmpBuf, Var->val_len);
            }
#if DEBUG_VARS_DECODE
            printf("VARS: Decoded OBJID (length %d) (%d bytes left)\n",
                   Var->val_len, ThisVarLen);
#endif
            break;

        case ASN_NULL:
