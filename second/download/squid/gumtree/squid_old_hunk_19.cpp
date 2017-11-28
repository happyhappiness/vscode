
        /* Is it valid? */
        if (VarBindType != (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR)) {
            snmp_set_api_error(SNMPERR_PDU_PARSE);
            PARSE_ERROR;
        }
#ifdef DEBUG_VARS_DECODE
        printf("VARS: Header type 0x%x (%d bytes left)\n", VarBindType, ThisVarLen);
#endif

        /* Parse the OBJID */
        bufp = asn_parse_objid(bufp, &ThisVarLen, &VarBindType,
                               Var->name, &(Var->name_length));
