ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                     "worker %s already used by another worker", worker->name);