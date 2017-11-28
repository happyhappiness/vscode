    struct variable_list *Var = NULL, **VarLastP;
    u_char *bufp, *tmp;
    u_char VarBindType;
    u_char *DataPtr;
    int DataLen;
    oid TmpBuf[MAX_NAME_LEN];
    memset(TmpBuf, 0, MAX_NAME_LEN * sizeof(*TmpBuf));

    int AllVarLen = *BufLen;
    int ThisVarLen = 0;

    VarLastP = VarP;
#if DEBUG_VARS_DECODE
    printf("VARS: Decoding buffer of length %d\n", *BufLen);
#endif

    /* Now parse the variables */
    bufp = asn_parse_header(Buffer, &AllVarLen, &VarBindType);
    if (bufp == NULL)
        return (NULL);

    if (VarBindType != (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR)) {
        snmp_set_api_error(SNMPERR_PDU_PARSE);
        return (NULL);
    }
#if DEBUG_VARS_DECODE
    printf("VARS: All Variable length %d\n", AllVarLen);
#endif

#define PARSE_ERROR { snmp_var_free(Var); return(NULL); }

    /* We know how long the variable list is.  Parse it. */
