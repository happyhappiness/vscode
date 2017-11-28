u_char *
asn_parse_length(u_char * data, u_int * length)
/*    u_char  *data;   IN - pointer to start of length field */
/*    u_int  *length; OUT - value of length field */
{
    u_char lengthbyte = *data;

    if (lengthbyte & ASN_LONG_LEN) {
        lengthbyte &= ~ASN_LONG_LEN;    /* turn MSb off */

        if (lengthbyte == 0) {
            snmp_set_api_error(SNMPERR_ASN_DECODE);
            return (NULL);
        }
        if (lengthbyte > sizeof(int)) {
            snmp_set_api_error(SNMPERR_ASN_DECODE);
            return (NULL);
        }
        *length = (u_int) 0;
        memcpy((char *) (length), (char *) data + 1, (int) lengthbyte);
        *length = ntohl(*length);
        *length >>= (8 * ((sizeof *length) - lengthbyte));
        return (data + lengthbyte + 1);

    }
    /* short asnlength */

    *length = (int) lengthbyte;
    return (data + 1);
}