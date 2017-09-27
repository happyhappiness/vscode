    if ((remotehost == NULL) || remotehost_is_ip) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01753)
                      "access check of '%s' to %s failed, reason: unable to get the "
                      "remote host name", require_line, r->uri);
    }
    else {
        const char *err = NULL;
        const ap_expr_info_t *expr = parsed_require_line;
        const char *require;

        require = ap_expr_str_exec(r, expr, &err);
        if (err) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02593)
                          "authz_host authorize: require host: Can't "
                          "evaluate require expression: %s", err);
            return AUTHZ_DENIED;
        }

        /* The 'host' provider will allow the configuration to specify a list of
            host names to check rather than a single name.  This is different
            from the previous host based syntax. */
        t = require;
        while ((w = ap_getword_conf(r->pool, &t)) && w[0]) {
            if (in_domain(w, remotehost)) {
                return AUTHZ_GRANTED;
            }
        }
    }
