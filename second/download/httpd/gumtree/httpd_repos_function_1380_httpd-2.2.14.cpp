static int form_header_field(header_struct *h,
                             const char *fieldname, const char *fieldval)
{
#if APR_CHARSET_EBCDIC
    char *headfield;
    apr_size_t len;
    apr_size_t name_len;
    apr_size_t val_len;
    char *next;

    name_len = strlen(fieldname);
    val_len = strlen(fieldval);
    len = name_len + val_len + 4; /* 4 for ": " plus CRLF */
    headfield = (char *)apr_palloc(h->pool, len + 1);
    memcpy(headfield, fieldname, name_len);
    next = headfield + name_len;
    *next++ = ':';
    *next++ = ' ';
    memcpy(next, fieldval, val_len);
    next += val_len;
    *next++ = CR;
    *next++ = LF;
    *next = 0;
    ap_xlate_proto_to_ascii(headfield, len);
    apr_brigade_write(h->bb, NULL, NULL, headfield, len);
#else
    struct iovec vec[4];
    struct iovec *v = vec;
    v->iov_base = (void *)fieldname;
    v->iov_len = strlen(fieldname);
    v++;
    v->iov_base = ": ";
    v->iov_len = sizeof(": ") - 1;
    v++;
    v->iov_base = (void *)fieldval;
    v->iov_len = strlen(fieldval);
    v++;
    v->iov_base = CRLF;
    v->iov_len = sizeof(CRLF) - 1;
    apr_brigade_writev(h->bb, NULL, NULL, vec, 4);
#endif /* !APR_CHARSET_EBCDIC */
    return 1;
}