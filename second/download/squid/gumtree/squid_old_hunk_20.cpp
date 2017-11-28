        if (VarBindType != (u_char) (ASN_UNIVERSAL |
                                     ASN_PRIMITIVE |
                                     ASN_OBJECT_ID)) {
            snmp_set_api_error(SNMPERR_PDU_PARSE);
            PARSE_ERROR;
        }
#ifdef DEBUG_VARS_DECODE
        printf("VARS: Decoded OBJID (%d bytes). (%d bytes left)\n",
               Var->name_length, ThisVarLen);
#endif

        /* Keep a pointer to this object */
        DataPtr = bufp;
