u_char *
snmp_var_DecodeVarBind(u_char * Buffer, int *BufLen,
                       struct variable_list ** VarP,
                       int Version)
{
    struct variable_list *Var = NULL, **VarLastP;
    u_char *bufp, *tmp;
    u_char VarBindType;
    u_char *DataPtr;
    int DataLen;
    oid TmpBuf[MAX_NAME_LEN];

    int AllVarLen = *BufLen;
    int ThisVarLen = 0;

    VarLastP = VarP;
#ifdef DEBUG_VARS_DECODE
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
#ifdef DEBUG_VARS_DECODE
    printf("VARS: All Variable length %d\n", AllVarLen);
#endif

#define PARSE_ERROR { snmp_var_free(Var); return(NULL); }

    /* We know how long the variable list is.  Parse it. */
    while ((int) AllVarLen > 0) {

        /* Create a new variable */
        Var = snmp_var_new(NULL, MAX_NAME_LEN);
        if (Var == NULL)
            return (NULL);

        /* Parse the header to find out the length of this variable. */
        ThisVarLen = AllVarLen;
        tmp = asn_parse_header(bufp, &ThisVarLen, &VarBindType);
        if (tmp == NULL)
            PARSE_ERROR;

        /* Now that we know the length , figure out how it relates to
         * the entire variable list
         */
        AllVarLen = AllVarLen - (ThisVarLen + (tmp - bufp));
        bufp = tmp;

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
        if (bufp == NULL)
            PARSE_ERROR;

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
        DataLen = ThisVarLen;

        /* find out type of object */
        bufp = asn_parse_header(bufp, &ThisVarLen, &(Var->type));
        if (bufp == NULL)
            PARSE_ERROR;
        ThisVarLen = DataLen;

#ifdef DEBUG_VARS_DECODE
        printf("VARS: Data type %d\n", Var->type);
#endif

        /* Parse the type */

        switch ((short) Var->type) {

        case ASN_INTEGER:
            Var->val.integer = (int *) xmalloc(sizeof(int));
            if (Var->val.integer == NULL) {
                snmp_set_api_error(SNMPERR_OS_ERR);
                PARSE_ERROR;
            }
            Var->val_len = sizeof(int);
            bufp = asn_parse_int(DataPtr, &ThisVarLen,
                                 &Var->type, (int *) Var->val.integer,
                                 Var->val_len);
#ifdef DEBUG_VARS_DECODE
            printf("VARS: Decoded integer '%d' (%d bytes left)\n",
                   *(Var->val.integer), ThisVarLen);
#endif
            break;

        case SMI_COUNTER32:
        case SMI_GAUGE32:
            /*  case SMI_UNSIGNED32: */
        case SMI_TIMETICKS:
            Var->val.integer = (int *) xmalloc(sizeof(u_int));
            if (Var->val.integer == NULL) {
                snmp_set_api_error(SNMPERR_OS_ERR);
                PARSE_ERROR;
            }
            Var->val_len = sizeof(u_int);
            bufp = asn_parse_unsigned_int(DataPtr, &ThisVarLen,
                                          &Var->type, (u_int *) Var->val.integer,
                                          Var->val_len);
#ifdef DEBUG_VARS_DECODE
            printf("VARS: Decoded timeticks '%d' (%d bytes left)\n",
                   *(Var->val.integer), ThisVarLen);
#endif
            break;

        case ASN_OCTET_STR:
        case SMI_IPADDRESS:
        case SMI_OPAQUE:
            Var->val_len = *&ThisVarLen;	/* String is this at most */
            Var->val.string = (u_char *) xmalloc((unsigned) Var->val_len);
            if (Var->val.string == NULL) {
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
            Var->val_len = MAX_NAME_LEN;
            bufp = asn_parse_objid(DataPtr, &ThisVarLen,
                                   &Var->type, TmpBuf, &Var->val_len);
            Var->val_len *= sizeof(oid);
            Var->val.objid = (oid *) xmalloc((unsigned) Var->val_len);
            if (Var->val.integer == NULL) {
                snmp_set_api_error(SNMPERR_OS_ERR);
                PARSE_ERROR;
            }
            /* Only copy if we successfully decoded something */
            if (bufp) {
                xmemcpy((char *) Var->val.objid, (char *) TmpBuf, Var->val_len);
            }
#ifdef DEBUG_VARS_DECODE
            printf("VARS: Decoded OBJID (length %d) (%d bytes left)\n",
                   Var->val_len, ThisVarLen);
#endif
            break;

        case ASN_NULL:
        case SMI_NOSUCHINSTANCE:
        case SMI_NOSUCHOBJECT:
        case SMI_ENDOFMIBVIEW:
            break;

        case SMI_COUNTER64:
            snmplib_debug(2, "Unable to parse type SMI_COUNTER64!\n");
            snmp_set_api_error(SNMPERR_UNSUPPORTED_TYPE);
            PARSE_ERROR;

        default:
            snmplib_debug(2, "bad type returned (%x)\n", Var->type);
            snmp_set_api_error(SNMPERR_PDU_PARSE);
            PARSE_ERROR;
        }			/* End of var type switch */

        if (bufp == NULL)
            PARSE_ERROR;

#ifdef DEBUG_VARS_DECODE
        printf("VARS:  Adding to list.\n");
#endif
        /* Add variable to the list */
        *VarLastP = Var;
        VarLastP = &(Var->next_variable);
    }
#undef PARSE_ERROR

    return (bufp);
}