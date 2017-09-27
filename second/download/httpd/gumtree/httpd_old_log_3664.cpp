ap_log_perror(APLOG_MARK, APLOG_WARNING, 0,
                          cmd->pool, "module %s is already loaded, skipping",
                          modname);