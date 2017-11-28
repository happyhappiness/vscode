u_char *
asn_parse_unsigned_int(u_char * data, int *datalength,
                       u_char * type, u_int * intp, int intsize)
/*    u_char *data;          IN     - pointer to start of object */
/*    int    *datalength;    IN/OUT - # of valid bytes left in buffer */
/*    u_char *type;          OUT    - asn type of object */
/*    u_int *intp;           IN/OUT - pointer to start of output buffer */
/*    int     intsize;       IN     - size of output buffer */
{
    /*
     * ASN.1 integer ::= 0x02 asnlength byte {byte}*
     */
    u_char *bufp = data;
    u_int asn_length;
    int value = 0;

    /* Room to store int? */
    if (intsize != sizeof(int)) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    /* Type */
    *type = *bufp++;

    /* Extract length */
    bufp = asn_parse_length(bufp, &asn_length);
    if (bufp == NULL)
        return (NULL);

    /* Make sure the entire int is in the buffer */
    if (asn_length + (bufp - data) > *datalength) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    /* Can we store this int? */
    if ((asn_length > (intsize + 1)) ||
            ((asn_length == intsize + 1) && *bufp != 0x00)) {
        snmp_set_api_error(SNMPERR_ASN_DECODE);
        return (NULL);
    }
    /* Remaining data */
    *datalength -= (int) asn_length + (bufp - data);

    /* Is the int negative? */
    if (*bufp & 0x80)
        value = -1;     /* integer is negative */

    /* Extract the bytes */
    while (asn_length--)
        value = (value << 8) | *bufp++;

    /* That's it! */
    *intp = value;
    return (bufp);
}