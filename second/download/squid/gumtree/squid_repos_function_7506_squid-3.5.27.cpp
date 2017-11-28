u_char *
asn_parse_objid(u_char * data, int *datalength,
                u_char * type, oid * objid, int *objidlength)
/*    u_char  *data;        IN - pointer to start of object */
/*    int     *datalength;  IN/OUT - # of valid bytes left in buf */
/*    u_char  *type;        OUT - ASN type of object */
/*    oid     *objid;       IN/OUT - pointer to start of output buffer */
/*    int     *objidlength; IN/OUT - number of sub-id's in objid */
{
    /*
     * ASN.1 objid ::= 0x06 asnlength subidentifier {subidentifier}*
     * subidentifier ::= {leadingbyte}* lastbyte
     * leadingbyte ::= 1 7bitvalue
     * lastbyte ::= 0 7bitvalue
     */
    u_char *bufp = data;
    oid *oidp = objid + 1;
    u_int subidentifier;
    int length;
    u_int asn_length;

    *type = *bufp++;
    bufp = asn_parse_length(bufp, &asn_length);
    if (bufp == NULL)
        return (NULL);

    if (asn_length + (bufp - data) > *datalength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    *datalength -= (int) asn_length + (bufp - data);

    /* Handle invalid object identifier encodings of the form 06 00 robustly */
    if (asn_length == 0)
        objid[0] = objid[1] = 0;

    length = asn_length;
    (*objidlength)--;       /* account for expansion of first byte */
    while (length > 0 && (*objidlength)-- > 0) {
        subidentifier = 0;

        do {            /* shift and add in low order 7 bits */
            subidentifier = (subidentifier << 7)
                            + (*(u_char *) bufp & ~ASN_BIT8);
            length--;
        } while (*(u_char *) bufp++ & ASN_BIT8);

        /* while last byte has high bit clear */
        if (subidentifier > (u_int) MAX_SUBID) {
            snmp_set_api_error(SNMPERR_ASN_DECODE);
            return (NULL);
        }
        *oidp++ = (oid) subidentifier;
    }

    /*
     * The first two subidentifiers are encoded into the first component
     * with the value (X * 40) + Y, where:
     *  X is the value of the first subidentifier.
     *  Y is the value of the second subidentifier.
     */
    subidentifier = (u_int) objid[1];
    if (subidentifier == 0x2B) {
        objid[0] = 1;
        objid[1] = 3;
    } else {
        objid[1] = (u_char) (subidentifier % 40);
        objid[0] = (u_char) ((subidentifier - objid[1]) / 40);
    }

    *objidlength = (int) (oidp - objid);
    return (bufp);
}