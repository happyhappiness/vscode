    if (strncasecmp(url, "ftp:", 4) == 0) {
        url += 4;
    }
    else {
        return DECLINED;
    }
    def_port = apr_uri_port_of_scheme("ftp");

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: FTP: canonicalising URL %s", url);

    port = def_port;
    err = ap_proxy_canon_netloc(p, &url, &user, &password, &host, &port);
