ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0,
                          cmd->pool,
                          "Warning: DocumentRoot [%s] does not exist",
                          arg);