void ap_add_output_filters_by_type(request_rec *r)
{
    core_dir_config *conf;
    const char *ctype;

    conf = (core_dir_config *)ap_get_module_config(r->per_dir_config,
                                                   &core_module);

    /* We can't do anything with no content-type or if we don't have a
     * filter configured.
     */
    if (!r->content_type || !conf->ct_output_filters) {
        return;
    }

    /* remove c-t decoration */
    ctype = ap_field_noparam(r->pool, r->content_type);
    if (ctype) {
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