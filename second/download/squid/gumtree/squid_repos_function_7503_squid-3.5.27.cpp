u_char *
asn_build_header_with_truth(u_char * data, int *datalength,
                            u_char type, int length, int truth)
/*    u_char *data;       IN - pointer to start of object */
/*    int    *datalength; IN/OUT - # of valid bytes left in buffer */
/*    u_char  type;       IN - ASN type of object */
/*    int     length;     IN - length of object */
/*    int     truth;      IN - Whether length is truth */
{
    if (*datalength < 1) {
        snmp_set_api_error(SNMPERR_ASN_ENCODE);
        return (NULL);
    }
    *data++ = type;
    (*datalength)--;
    return (asn_build_length(data, datalength, length, truth));
}