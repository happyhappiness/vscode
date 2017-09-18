    proxy_http_conn_t *p_conn = apr_pcalloc(r->connection->pool,
                                           sizeof(*p_conn));

    /* is it for us? */
    if (strncasecmp(url, "https:", 6) == 0) {
        if (!ap_proxy_ssl_enable(NULL)) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "proxy: HTTPS: declining URL %s"
                         " (mod_ssl not configured?)", url);
            return DECLINED;
        }
        is_ssl = 1;
    }
    else if (strncasecmp(url, "http:", 5)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: HTTP: declining URL %s", url);
        return DECLINED; /* only interested in HTTP */
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
             "proxy: HTTP: serving URL %s", url);
    
    
    /* only use stored info for top-level pages. Sub requests don't share 
     * in keepalives
     */
