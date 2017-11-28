u_char *
asn_build_length(u_char * data, int *datalength,
                 int length, int truth)
/*   u_char *data;       IN - pointer to start of object */
/*   int    *datalength; IN/OUT - # of valid bytes left in buf */
/*   int     length;     IN - length of object */
/*   int     truth;      IN - If 1, this is the true len. */
{
    u_char *start_data = data;

    if (truth) {

        /* no indefinite lengths sent */
        if (length < 0x80) {
            if (*datalength < 1) {
                snmp_set_api_error(SNMPERR_ASN_ENCODE);
                return (NULL);
            }
            *data++ = (u_char) length;

        } else if (length <= 0xFF) {
            if (*datalength < 2) {
                snmp_set_api_error(SNMPERR_ASN_ENCODE);
                return (NULL);
            }
            *data++ = (u_char) (0x01 | ASN_LONG_LEN);
            *data++ = (u_char) length;
        } else {		/* 0xFF < length <= 0xFFFF */
            if (*datalength < 3) {
                snmp_set_api_error(SNMPERR_ASN_ENCODE);
                return (NULL);
            }
            *data++ = (u_char) (0x02 | ASN_LONG_LEN);
            *data++ = (u_char) ((length >> 8) & 0xFF);
            *data++ = (u_char) (length & 0xFF);
        }

    } else {

        /* Don't know if this is the true length.  Make sure it's large
         * enough for later.
         */
        if (*datalength < 3) {
            snmp_set_api_error(SNMPERR_ASN_ENCODE);
            return (NULL);
        }
        *data++ = (u_char) (0x02 | ASN_LONG_LEN);
        *data++ = (u_char) ((length >> 8) & 0xFF);
        *data++ = (u_char) (length & 0xFF);
    }

    *datalength -= (data - start_data);
    return (data);
}