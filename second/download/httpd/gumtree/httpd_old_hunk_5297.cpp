    proxy_conn_rec *backend = NULL;
    char *scheme;
    int retry;
    conn_rec *c = r->connection;
    apr_pool_t *p = r->pool;
    apr_uri_t *uri;

    if (strncasecmp(url, "wss:", 4) == 0) {
        scheme = "WSS";
    }
    else if (strncasecmp(url, "ws:", 3) == 0) {
        scheme = "WS";
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02450) "declining URL %s", url);
