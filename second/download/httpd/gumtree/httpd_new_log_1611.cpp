ap_log_error(APLOG_MARK, level, status, r->server,
                     "dialog with client %pI failed",
                     r->connection->remote_addr);