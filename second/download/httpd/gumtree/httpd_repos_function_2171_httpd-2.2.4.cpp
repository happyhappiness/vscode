int ap_rvputs_proto_in_ascii(request_rec *r, ...)
{
    va_list va;
    const char *s;
    char *ascii_s;
    apr_size_t len;
    apr_size_t written = 0;

    va_start(va, r);
    while (1) {
        s = va_arg(va, const char *);
        if (s == NULL)
            break;
        len = strlen(s);
        ascii_s = apr_pstrndup(r->pool, s, len);
        ap_xlate_proto_to_ascii(ascii_s, len);
        if (ap_rputs(ascii_s, r) < 0)
            return -1;
        written += len;
    }
    va_end(va);

    return written;
}