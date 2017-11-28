u_char *
asn_build_string(u_char * data, int *datalength,
                 u_char type, u_char * string, int strlength)
/*    u_char *data;       IN - pointer to start of object */
/*    int    *datalength; IN/OUT - # of valid bytes left in buf */
/*    u_char  type;       IN - ASN type of string */
/*    u_char *string;     IN - pointer to start of input buffer */
/*    int     strlength;  IN - size of input buffer */
{
    /*
     * ASN.1 octet string ::= primstring | cmpdstring
     * primstring ::= 0x04 asnlength byte {byte}*
     * cmpdstring ::= 0x24 asnlength string {string}*
     * This code will never send a compound string.
     */
    data = asn_build_header_with_truth(data, datalength, type, strlength, 1);
    if (data == NULL)
        return (NULL);

    if (*datalength < strlength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    memcpy((char *) data, (char *) string, strlength);
    *datalength -= strlength;
    return (data + strlength);
}