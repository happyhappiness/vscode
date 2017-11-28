u_char *
asn_build_header(u_char * data, /* IN - ptr to start of object */
                 int *datalength,       /* IN/OUT - # of valid bytes */
                 /*          left in buffer */
                 u_char type,       /* IN - ASN type of object */
                 int length)
{   /* IN - length of object */
    /* Truth is 0 'cause we don't know yet */
    return (asn_build_header_with_truth(data, datalength, type, length, 0));
}