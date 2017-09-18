ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0,
                          cmd->pool,
                          "Warning: DocumentRoot [%s] does not exist",
                          arg);