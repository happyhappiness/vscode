    if ((dc->nOptions & SSL_OPT_FAKEBASICAUTH) == 0 && dc->szUserName) {
        char *val = ssl_var_lookup(r->pool, r->server, r->connection,
                                   r, (char *)dc->szUserName);
        if (val && val[0])
            r->user = val;
        else
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Failed to set r->user to '%s'", dc->szUserName);
    }

    /*
     * Check SSLRequire boolean expressions
     */
    requires = dc->aRequirement;
    ssl_requires = (ssl_require_t *)requires->elts;

    for (i = 0; i < requires->nelts; i++) {
        ssl_require_t *req = &ssl_requires[i];
        ok = ssl_expr_exec(r, req->mpExpr);

        if (ok < 0) {
            cp = apr_psprintf(r->pool,
                              "Failed to execute "
                              "SSL requirement expression: %s",
                              ssl_expr_get_error());

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "access to %s failed, reason: %s",
                          r->filename, cp);

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");

            return HTTP_FORBIDDEN;
        }

        if (ok != 1) {
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Access to %s denied for %s "
                          "(requirement expression not fulfilled)",
                          r->filename, r->connection->remote_ip);

            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Failed expression: %s", req->cpExpr);

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "access to %s failed, reason: %s",
                          r->filename,
                          "SSL requirement expression not fulfilled");

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");
