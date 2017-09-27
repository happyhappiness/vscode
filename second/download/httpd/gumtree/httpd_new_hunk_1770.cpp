     */
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
