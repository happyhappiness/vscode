static apr_off_t get_content_length(request_rec * r)
{
    apr_off_t len = 0;

    if (r->main == NULL) {
        const char *clp = apr_table_get(r->headers_in, "Content-Length");

        if (clp) {
            char *errp;
            if (apr_strtoff(&len, clp, &errp, 10) || *errp || len < 0) {
                len = 0; /* parse error */
            }
        }
    }

    return len;
}