    proxy_dir_conf *dconf;

    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
    psc = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    r->headers_out = apr_table_make(r->pool, 20);
    *pread_len = 0;

    /*
     * Read header lines until we get the empty separator line, a read error,
     * the connection closes (EOF), or we timeout.
     */
    ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                  "Headers received from backend:");
    while ((len = ap_getline(buffer, size, rr, 1)) > 0) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "%s", buffer);

        if (!(value = strchr(buffer, ':'))) {     /* Find the colon separator */

            /* We may encounter invalid headers, usually from buggy
             * MS IIS servers, so we need to determine just how to handle
             * them. We can either ignore them, assume that they mark the
