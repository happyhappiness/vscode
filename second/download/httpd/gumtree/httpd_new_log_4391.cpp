ap_log_error(APLOG_MARK, APLOG_ERR, errno, cmd->server, APLOGNO(02172)
                     "%s: getrlimit failed", cmd->cmd->name);