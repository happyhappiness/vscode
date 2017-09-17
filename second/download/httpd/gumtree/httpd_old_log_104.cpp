ap_log_error(APLOG_MARK, APLOG_INFO, r->server,
                     "%s client stopped connection before send mmap completed",
                                ap_get_remote_host(r->connection,
                                                r->per_dir_config,
                                                REMOTE_NAME));