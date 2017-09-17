ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                            "access to %s failed for %s", r->uri,
                            ap_get_remote_host(r->connection, r->per_dir_config,
                                            REMOTE_NOLOOKUP));