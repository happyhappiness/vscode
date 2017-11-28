u_char *
asn_build_exception(u_char * data, int *datalength, u_char type)
/*    u_char  *data;       IN - pointer to start of object */
/*    int     *datalength; IN/OUT - # of valid bytes left in buf */
/*    u_char   type;       IN - ASN type of object */
{
    return (asn_build_header_with_truth(data, datalength, type, 0, 1));
}