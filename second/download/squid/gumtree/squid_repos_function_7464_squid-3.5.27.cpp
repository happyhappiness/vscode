u_char *
snmp_var_EncodeVarBind(u_char * Buffer, int *BufLenP,
                       variable_list * VarList,
                       int Version)
{
    struct variable_list *Vars;
    u_char *bufp;
    u_char *HeaderStart;
    u_char *HeaderEnd;
    int FakeArg = *BufLenP;

    bufp = Buffer;

    for (Vars = VarList; Vars; Vars = Vars->next_variable) {

        /* Build the header for this variable
         *
         * Use Maximum size.
         */
        HeaderStart = bufp;
        HeaderEnd = asn_build_header(HeaderStart, BufLenP,
                                     (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                                     FakeArg);
        if (HeaderEnd == NULL)
            return (NULL);

        /* Now, let's put the Object Identifier into the buffer */
        bufp = asn_build_objid(HeaderEnd, BufLenP,
                               (u_char) (ASN_UNIVERSAL |
                                         ASN_PRIMITIVE |
                                         ASN_OBJECT_ID),
                               Vars->name, Vars->name_length);
        if (bufp == NULL)
            return (NULL);

        /* Now put the data in */
        switch (Vars->type) {

        case ASN_INTEGER:
            bufp = asn_build_int(bufp,
                                 BufLenP, Vars->type,
                                 (int *) Vars->val.integer, Vars->val_len);
            break;

        case SMI_COUNTER32:
        case SMI_GAUGE32:
        /*  case SMI_UNSIGNED32: */
        case SMI_TIMETICKS:
            bufp = asn_build_unsigned_int(bufp, BufLenP,
                                          Vars->type,
                                          (u_int *) Vars->val.integer, Vars->val_len);
            break;

        case ASN_OCTET_STR:
        case SMI_IPADDRESS:
        case SMI_OPAQUE:
            bufp = asn_build_string(bufp, BufLenP, Vars->type,
                                    Vars->val.string, Vars->val_len);
            break;

        case ASN_OBJECT_ID:
            bufp = asn_build_objid(bufp, BufLenP, Vars->type,
                                   (oid *) Vars->val.objid, Vars->val_len / sizeof(oid));
            break;

        case SMI_NOSUCHINSTANCE:
        case SMI_NOSUCHOBJECT:
        case SMI_ENDOFMIBVIEW:
            if (Version == SNMP_VERSION_1) {
                /* SNMP Version 1 does not support these error codes. */
                bufp = asn_build_null(bufp, BufLenP, SMI_NOSUCHOBJECT);
            } else {
                bufp = asn_build_exception(bufp, BufLenP, Vars->type);
            }
            break;

        case ASN_NULL:
            bufp = asn_build_null(bufp, BufLenP, Vars->type);
            break;

        case SMI_COUNTER64:
            snmplib_debug(2, "Unable to encode type SMI_COUNTER64!\n");
        /* Fall through */

        default:
            snmp_set_api_error(SNMPERR_UNSUPPORTED_TYPE);
            return (NULL);
        }

        /* ASSERT:  bufp should now point to the next valid byte. */
        if (bufp == NULL)
            return (NULL);

        /* Rebuild the header with the appropriate length */
        HeaderEnd = asn_build_header(HeaderStart, &FakeArg,
                                     (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                                     (bufp - HeaderEnd));

        /* Returns NULL */
        if (HeaderEnd == NULL)
            return (NULL);

    }

    /* or the end of the entire thing */
    return (bufp);
}