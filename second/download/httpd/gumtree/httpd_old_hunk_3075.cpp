
    url = apr_pstrdup(r->pool, &url[1]);    /* make it point to "//", which is what proxy_canon_netloc expects */

    err = ap_proxy_canon_netloc(r->pool, &url, &user, &password, &host, &port);

    if (err != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "%s", err);
    }

    r->hostname = host;

    return host;        /* ought to return the port, too */
}
