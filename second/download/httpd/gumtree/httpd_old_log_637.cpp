r(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, cmd->server,
                 "Platform does not support rlimit for %s", cmd->cmd->name);