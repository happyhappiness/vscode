            apr_table_setn(r->err_headers_out, "Upgrade", "TLS/1.0, HTTP/1.1");
            apr_table_setn(r->err_headers_out, "Connection", "Upgrade");

            return HTTP_UPGRADE_REQUIRED;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02219)
                      "access to %s failed, reason: %s",
                      r->filename, "SSL connection required");

        /* remember forbidden access for strict require option */
        apr_table_setn(r->notes, "ssl-access-forbidden", "1");

