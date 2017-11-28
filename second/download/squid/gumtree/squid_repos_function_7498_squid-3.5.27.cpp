u_char *
asn_build_int(u_char * data, int *datalength,
              u_char type, int *intp, int intsize)
/*     u_char *data;         IN - pointer to start of output buffer */
/*     int    *datalength;   IN/OUT - # of valid bytes left in buffer */
/*     u_char  type;         IN - asn type of object */
/*     int   *intp;          IN - pointer to start of integer */
/*     int    intsize;       IN - size of *intp */
{
    /*
     * ASN.1 integer ::= 0x02 asnlength byte {byte}*
     */
    int integer;
    u_int mask;

    if (intsize != sizeof(int)) {
        snmp_set_api_error(SNMPERR_ASN_ENCODE);
        return (NULL);
    }
    integer = *intp;

    /*
     * Truncate "unnecessary" bytes off of the most significant end of this
     * 2's complement integer.  There should be no sequence of 9
     * consecutive 1's or 0's at the most significant end of the
     * integer.
     */
    mask = (u_int) 0x1FF << ((8 * (sizeof(int) - 1)) - 1);
    /* mask is 0xFF800000 on a big-endian machine */

    while ((((integer & mask) == 0) || ((integer & mask) == mask))
            && intsize > 1) {
        intsize--;
        integer <<= 8;
    }

    data = asn_build_header_with_truth(data, datalength, type, intsize, 1);
    if (data == NULL)
        return (NULL);

    /* Enough room for what we just encoded? */
    if (*datalength < intsize) {
        snmp_set_api_error(SNMPERR_ASN_ENCODE);
        return (NULL);
    }
    /* Insert it */
    *datalength -= intsize;
    mask = (u_int) 0xFF << (8 * (sizeof(int) - 1));
    /* mask is 0xFF000000 on a big-endian machine */
    while (intsize--) {
        *data++ = (u_char) ((integer & mask) >> (8 * (sizeof(int) - 1)));
        integer <<= 8;
    }
    return (data);
}