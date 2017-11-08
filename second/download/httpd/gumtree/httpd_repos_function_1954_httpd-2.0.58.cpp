void ap_add_output_filters_by_type(request_rec *r)
{
    core_dir_config *conf;
    const char *ctype, *ctypes;

    conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                   &core_module);

    /* We can't do anything with proxy requests, no content-types or if
     * we don't have a filter configured.
     */
    if (r->proxyreq != PROXYREQ_NONE || !r->content_type ||
        !conf->ct_output_filters) {
        return;
    }

    ctypes = r->content_type;

    /* We must be able to handle decorated content-types.  */
    while (*ctypes && (ctype = ap_getword(r->pool, &ctypes, ';'))) {
        ap_filter_rec_t *ct_filter;
        ct_filter = apr_hash_get(conf->ct_output_filters, ctype,
                                 APR_HASH_KEY_STRING);
        while (ct_filter) {
            ap_add_output_filter(ct_filter->name, NULL, r, r->connection);
            ct_filter = ct_filter->next;
        }
    }

    return;
}