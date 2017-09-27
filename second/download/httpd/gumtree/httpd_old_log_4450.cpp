ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server,
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         worker->name, new->real);