ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, cmd->server,
                     "PassEnv variable %s was undefined", arg);