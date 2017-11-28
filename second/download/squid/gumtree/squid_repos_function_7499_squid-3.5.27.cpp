u_char *
asn_build_unsigned_int(u_char * data, int *datalength,
                       u_char type, u_int * intp, int intsize)
/*     u_char *data;         IN     - pointer to start of output buffer */
/*     int    *datalength;   IN/OUT - # of valid bytes left in buffer */
/*     u_char  type;         IN     - asn type of object */
/*     u_int  *intp;         IN     - pointer to start of integer */
/*     int     intsize;      IN     - size of *intp */
{
    /*
     * ASN.1 integer ::= 0x02 asnlength byte {byte}*
     */
    u_int integer;
    u_int mask;
    int add_null_byte = 0;

    if (intsize != sizeof(int)) {
        snmp_set_api_error(SNMPERR_ASN_ENCODE);
        return (NULL);
    }
    integer = *intp;
    mask = (u_int) 0x80 << (8 * (sizeof(int) - 1));
    /* mask is 0x80000000 on a big-endian machine */
    if ((integer & mask) != 0) {
        /* add a null byte if MSB is set, to prevent sign extension */
        add_null_byte = 1;
        intsize++;
    }
    /*
     * Truncate "unnecessary" bytes off of the most significant end of
     * this 2's complement integer.
     * There should be no sequence of 9 consecutive 1's or 0's at the
     * most significant end of the integer.
     * The 1's case is taken care of above by adding a null byte.
     */
    mask = (u_int) 0x1FF << ((8 * (sizeof(int) - 1)) - 1);
    /* mask is 0xFF800000 on a big-endian machine */
    while (((integer & mask) == 0) && intsize > 1) {
        intsize--;
        integer <<= 8;
    }

    data = asn_build_header_with_truth(data, datalength, type, intsize, 1);
    if (data == NULL)
        return (NULL);

    if (*datalength < intsize) {
        snmp_set_api_error(SNMPERR_ASN_ENCODE);
        return (NULL);
    }
    *datalength -= intsize;
    if (add_null_byte == 1) {
        *data++ = '\0';
        intsize--;
    }
    mask = (u_int) 0xFF << (8 * (sizeof(int) - 1));
    /* mask is 0xFF000000 on a big-endian machine */
    while (intsize--) {
        *data++ = (u_char) ((integer & mask) >> (8 * (sizeof(int) - 1)));
        integer <<= 8;
    }
    return (data);
}