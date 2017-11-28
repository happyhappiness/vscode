u_char *
asn_build_null(u_char * data, int *datalength, u_char type)
/*    u_char  *data;       IN - pointer to start of object */
/*    int     *datalength; IN/OUT - # of valid bytes left in buf */
/*    u_char   type;       IN - ASN type of object */
{
    /*
     * ASN.1 null ::= 0x05 0x00
     */
    return (asn_build_header_with_truth(data, datalength, type, 0, 1));
}