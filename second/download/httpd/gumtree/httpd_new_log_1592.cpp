ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "TLS session ticket key for %s successfully loaded from %s",
                 (mySrvConfig(s))->vhost_id, path);