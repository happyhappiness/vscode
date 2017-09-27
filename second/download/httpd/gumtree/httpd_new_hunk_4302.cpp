                              apr_port_t proxyport)
{
    int status;
    char server_portstr[32];
    conn_rec *origin = NULL;
    proxy_conn_rec *backend = NULL;
    apr_uri_t *uri;

    proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                 &proxy_module);

    apr_pool_t *p = r->pool;


    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01076)
                  "url: %s proxyname: %s proxyport: %d",
                  url, proxyname, proxyport);

    if (strncasecmp(url, "fcgi:", 5) != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01077) "declining URL %s", url);
        return DECLINED;
    }

