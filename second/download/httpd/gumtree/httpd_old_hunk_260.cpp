    }
    else {
        return DECLINED;
    }
    def_port = apr_uri_default_port_for_scheme(scheme);

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r->server,
             "proxy: HTTP: canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    port = def_port;
