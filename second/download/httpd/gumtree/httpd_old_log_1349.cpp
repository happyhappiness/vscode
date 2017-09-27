ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "Access to %s denied for %s "
                         "(requirement expression not fulfilled)",
                         r->filename, r->connection->remote_ip);