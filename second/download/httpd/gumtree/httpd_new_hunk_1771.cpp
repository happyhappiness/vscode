            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Failed expression: %s", req->cpExpr);

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "access to %s failed, reason: %s",
                          r->filename,
                          "SSL requirement expression not fulfilled");

            /* remember forbidden access for strict require option */
            apr_table_setn(r->notes, "ssl-access-forbidden", "1");

            return HTTP_FORBIDDEN;
        }
