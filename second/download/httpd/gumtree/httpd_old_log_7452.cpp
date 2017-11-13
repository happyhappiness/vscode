ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01149)
                     "Sharing worker '%s' instead of creating new worker '%s'",
                     worker->s->name, name);