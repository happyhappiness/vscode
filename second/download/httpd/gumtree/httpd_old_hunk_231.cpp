    /* otherwise, try it direct */
    /* N.B. what if we're behind a firewall, where we must use a proxy or
     * give up??
     */

    /* handle the scheme */
    ap_log_error(APLOG_MARK, APLOG_DEBUG | APLOG_NOERRNO, 0, r->server,
                 "Trying to run scheme_handler");
    access_status = proxy_run_scheme_handler(r, conf, url, NULL, 0);
    if (DECLINED == access_status) {
        ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_NOERRNO, 0, r->server,
                    "proxy: No protocol handler was valid for the URL %s. "
                    "If you are using a DSO version of mod_proxy, make sure "
                    "the proxy submodules are included in the configuration "
                    "using LoadModule.", r->uri);
        return HTTP_FORBIDDEN;
    }
