u_char *
asn_parse_string(u_char * data, int *datalength,
                 u_char * type, u_char * string, int *strlength)
/*    u_char *data;       IN - pointer to start of object */
/*    int    *datalength; IN/OUT - # of valid bytes left in buffer */
/*    u_char *type;       OUT - asn type of object */
/*    u_char *string;     IN/OUT - pointer to start of output buffer */
/*    int    *strlength;  IN/OUT - size of output buffer */
{
    /*
     * ASN.1 octet string ::= primstring | cmpdstring
     * primstring ::= 0x04 asnlength byte {byte}*
     * cmpdstring ::= 0x24 asnlength string {string}*
     */
    u_char *bufp = data;
    u_int asn_length;

    *type = *bufp++;
    bufp = asn_parse_length(bufp, &asn_length);
    if (bufp == NULL)
        return (NULL);

    if (asn_length + (bufp - data) > *datalength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    if (asn_length > *strlength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    xmemcpy((char *) string, (char *) bufp, (int) asn_length);
    *strlength = (int) asn_length;
    *datalength -= (int) asn_length + (bufp - data);
    return (bufp + asn_length);
}