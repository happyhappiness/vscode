    /* stuff for PASV mode */
    int connect = 0, use_port = 0;
    char dates[AP_RFC822_DATE_LEN];

    /* is this for us? */
    if (proxyhost) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: declining URL %s - proxyhost %s specified:", url, proxyhost);
        return DECLINED;        /* proxy connections are via HTTP */
    }
    if (strncasecmp(url, "ftp:", 4)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: FTP: declining URL %s - not ftp:", url);
        return DECLINED;        /* only interested in FTP */
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: serving URL %s", url);

    /* create space for state information */
    backend = (proxy_conn_rec *) ap_get_module_config(c->conn_config, &proxy_ftp_module);
    if (!backend) {
        backend = ap_pcalloc(c->pool, sizeof(proxy_conn_rec));
