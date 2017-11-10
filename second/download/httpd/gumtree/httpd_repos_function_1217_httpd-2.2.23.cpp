static apr_array_header_t *do_header_line(apr_pool_t *p,
                                          const char *accept_line)
{
    apr_array_header_t *accept_recs;

    if (!accept_line) {
        return NULL;
    }

    accept_recs = apr_array_make(p, 40, sizeof(accept_rec));

    while (*accept_line) {
        accept_rec *new = (accept_rec *) apr_array_push(accept_recs);
        accept_line = get_entry(p, new, accept_line);
    }

    return accept_recs;
}