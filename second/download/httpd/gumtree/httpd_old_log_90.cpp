ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "request failed for %s, reason: URI too long",
            ap_get_remote_host(r->connection, r->per_dir_config, REMOTE_NAME));