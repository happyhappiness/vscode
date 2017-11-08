static int perchild_header_field(perchild_header *h,
                             const char *fieldname, const char *fieldval)
{
    apr_pstrcat(h->p, h->headers, fieldname, ": ", fieldval, CRLF, NULL); 
    return 1;
}