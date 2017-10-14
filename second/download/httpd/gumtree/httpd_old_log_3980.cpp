ap_log_perror(APLOG_MARK, APLOG_ERR, 0, lifecycle_pool,
                              "Loading lua file %s: %s",
                              spec->file, err);