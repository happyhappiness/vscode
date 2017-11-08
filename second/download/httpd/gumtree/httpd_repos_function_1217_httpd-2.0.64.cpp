static char *make_allow(request_rec *r)
{
    char *list;
    apr_int64_t mask;
    apr_array_header_t *allow = apr_array_make(r->pool, 10, sizeof(char *));
    apr_hash_index_t *hi = apr_hash_first(r->pool, methods_registry);
    /* For TRACE below */
    core_server_config *conf =
        ap_get_module_config(r->server->module_config, &core_module);

    mask = r->allowed_methods->method_mask;

    for (; hi; hi = apr_hash_next(hi)) {
        const void *key;
        void *val;

        apr_hash_this(hi, &key, NULL, &val);
        if ((mask & (AP_METHOD_BIT << *(int *)val)) != 0) {
            *(const char **)apr_array_push(allow) = key;

            /* the M_GET method actually refers to two methods */
            if (*(int *)val == M_GET)
                *(const char **)apr_array_push(allow) = "HEAD";
        }
    }

    /* TRACE is tested on a per-server basis */
    if (conf->trace_enable != AP_TRACE_DISABLE)
        *(const char **)apr_array_push(allow) = "TRACE";

    list = apr_array_pstrcat(r->pool, allow, ',');

    /* ### this is rather annoying. we should enforce registration of
       ### these methods */
    if ((mask & (AP_METHOD_BIT << M_INVALID))
        && (r->allowed_methods->method_list != NULL)
        && (r->allowed_methods->method_list->nelts != 0)) {
        int i;
        char **xmethod = (char **) r->allowed_methods->method_list->elts;

        /*
         * Append all of the elements of r->allowed_methods->method_list
         */
        for (i = 0; i < r->allowed_methods->method_list->nelts; ++i) {
            list = apr_pstrcat(r->pool, list, ",", xmethod[i], NULL);
        }
    }

    return list;
}