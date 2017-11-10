static char *lookup_header(request_rec *r, const char *name)
{
    const apr_array_header_t *hdrs_arr;
    const apr_table_entry_t *hdrs;
    int i;

    hdrs_arr = apr_table_elts(r->headers_in);
    hdrs = (const apr_table_entry_t *)hdrs_arr->elts;
    for (i = 0; i < hdrs_arr->nelts; ++i) {
        if (hdrs[i].key == NULL) {
            continue;
        }
        if (strcasecmp(hdrs[i].key, name) == 0) {
            apr_table_merge(r->notes, VARY_KEY_THIS, name);
            return hdrs[i].val;
        }
    }
    return NULL;
}