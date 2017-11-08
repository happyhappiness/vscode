static char *ssl_var_lookup_header(apr_pool_t *p, request_rec *r, const char *name)
{
    char *hdr = NULL;

    if ((hdr = (char *)apr_table_get(r->headers_in, name)) != NULL)
        hdr = apr_pstrdup(p, hdr);
    return hdr;
}