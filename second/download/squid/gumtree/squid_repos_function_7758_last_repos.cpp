u_char *
asn_parse_header(u_char * data, int *datalength, u_char * type)
/*    u_char  *data;       IN - pointer to start of object */
/*    int     *datalength; IN/OUT - # of valid bytes left in buffer */
/*    u_char  *type;       OUT - ASN type of object */
{
    u_char *bufp = data;
    int header_len;
    u_int asn_length;

    /* this only works on data types < 30, i.e. no extension octets */
    if (IS_EXTENSION_ID(*bufp)) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    *type = *bufp;
    bufp = asn_parse_length(bufp + 1, &asn_length);
    if (bufp == NULL)
        return (NULL);

    header_len = bufp - data;
    if (header_len + asn_length > *datalength || asn_length > (u_int)(2 << 18) ) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    *datalength = (int) asn_length;
    return (bufp);
}