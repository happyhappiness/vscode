ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, cmd->server,
                "%s not supported on this platform", cmd->cmd->name);