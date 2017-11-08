static void fcgi_header_from_array(fcgi_header *h, unsigned char a[])
{
    h->version         = a[FCGI_HDR_VERSION_OFFSET];
    h->type            = a[FCGI_HDR_TYPE_OFFSET];
    h->requestIdB1     = a[FCGI_HDR_REQUEST_ID_B1_OFFSET];
    h->requestIdB0     = a[FCGI_HDR_REQUEST_ID_B0_OFFSET];
    h->contentLengthB1 = a[FCGI_HDR_CONTENT_LEN_B1_OFFSET];
    h->contentLengthB0 = a[FCGI_HDR_CONTENT_LEN_B0_OFFSET];
    h->paddingLength   = a[FCGI_HDR_PADDING_LEN_OFFSET];
    h->reserved        = a[FCGI_HDR_RESERVED_OFFSET];
}