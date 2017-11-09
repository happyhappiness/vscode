static char *make_allow(request_rec *r)
{
    apr_int64_t mask;
    apr_array_header_t *allow = apr_array_make(r->pool, 10, sizeof(char *));
    apr_hash_index_t *hi = apr_hash_first(r->pool, methods_registry);
    /* For TRACE below */
    core_server_config *conf =
        ap_get_core_module_config(r->server->module_config);

    mask = r->allowed_methods->method_mask;

    for (; hi; hi = apr_hash_next(hi)) {
        const void *key;
        void *val;

        apr_hash_this(hi, &key, NULL, &val);
        if ((mask & (AP_METHOD_BIT << *(int *)val)) != 0) {
            APR_ARRAY_PUSH(allow, const char *) = key;
        }
    }

    /* TRACE is tested on a per-server basis */
    if (conf->trace_enable != AP_TRACE_DISABLE)
        *(const char **)apr_array_push(allow) = "TRACE";

    /* ### this is rather annoying. we should enforce registration of
       ### these methods */
    if ((mask & (AP_METHOD_BIT << M_INVALID))
        && (r->allowed_methods->method_list != NULL)
        && (r->allowed_methods->method_list->nelts != 0)) {
        apr_array_cat(allow, r->allowed_methods->method_list);
    }

    return apr_array_pstrcat(r->pool, allow, ',');
}