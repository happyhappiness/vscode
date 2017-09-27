    conn_rec *origin = NULL;
    proxy_conn_rec *backend = NULL;
    const char *scheme = "AJP";
    int retry;
    proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                 &proxy_module);
    apr_pool_t *p = r->pool;
    apr_uri_t *uri;

    if (strncasecmp(url, "ajp:", 4) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00894) "declining URL %s", url);
        return DECLINED;
    }

    uri = apr_palloc(p, sizeof(*uri));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00895) "serving URL %s", url);

    /* create space for state information */
    status = ap_proxy_acquire_connection(scheme, &backend, worker,
                                         r->server);
    if (status != OK) {
