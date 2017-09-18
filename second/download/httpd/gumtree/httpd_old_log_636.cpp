ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, cmd->server,
                         "Must be uid 0 to raise maximum %s", cmd->cmd->name);