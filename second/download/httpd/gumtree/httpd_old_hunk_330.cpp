        if (ok < 0) {
            cp = apr_psprintf(r->pool,
                              "Failed to execute "
                              "SSL requirement expression: %s",
                              ssl_expr_get_error());

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r, 
                          "access to %s failed, reason: %s",
                          r->filename, cp);

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");

            return HTTP_FORBIDDEN;
        }

        if (ok != 1) {
            ssl_log(r->server, SSL_LOG_INFO,
                    "Access to %s denied for %s "
                    "(requirement expression not fulfilled)",
                    r->filename, r->connection->remote_ip);

            ssl_log(r->server, SSL_LOG_INFO,
                    "Failed expression: %s", req->cpExpr);

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r, 
                          "access to %s failed, reason: %s",
                          r->filename,
                          "SSL requirement expression not fulfilled "
                          "(see SSL logfile for more details)");

            /* remember forbidden access for strict require option */
