        return DECLINED;
    }
    url += sizeof(SCHEME); /* Keep slashes */

    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00857)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }

    apr_snprintf(sport, sizeof(sport), ":%u", port);

    if (ap_strchr(host, ':')) { /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
                             r->proxyreq);
    if (!path) {
        return HTTP_BAD_REQUEST;
    }

    r->filename = apr_pstrcat(r->pool, "proxy:" SCHEME "://", host, sport, "/",
                              path, NULL);

    if (apr_table_get(r->subprocess_env, "proxy-scgi-pathinfo")) {
        r->path_info = apr_pstrcat(r->pool, "/", path, NULL);
    }

    return OK;
}


/*
 * Send a block of data, ensure, everything is sent
