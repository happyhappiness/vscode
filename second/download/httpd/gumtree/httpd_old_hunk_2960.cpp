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
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "error parsing URL %s: %s",
                      url, err);
        return HTTP_BAD_REQUEST;
    }

    /*
     * now parse path/search args, according to rfc1738:
