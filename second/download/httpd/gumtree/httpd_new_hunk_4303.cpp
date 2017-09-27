                        proxy_server_conf *conf, char *url,
                        const char *proxyname, apr_port_t proxyport)
{
    int status;
    proxy_conn_rec *backend = NULL;
    apr_pool_t *p = r->pool;
    apr_uri_t *uri;
    char dummy;

    if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00865)
                      "declining URL %s", url);
        return DECLINED;
