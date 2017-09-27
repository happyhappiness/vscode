        url += 4;
    }
    else {
        return DECLINED;
    }

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, r->server,
             "proxy: AJP: canonicalising URL %s", url);

    /*
     * do syntactic check.
     * We break the URL into host, port, path, search
     */
