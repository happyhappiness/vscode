ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                         elts[i].key, elts[i].val, worker->name);