ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                          "Access to %s denied for %s "
                          "(requirement expression not fulfilled)",
                          r->filename, r->connection->remote_ip);