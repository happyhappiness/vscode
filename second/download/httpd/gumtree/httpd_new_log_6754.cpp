ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(01150)
                         "Ignoring parameter '%s=%s' for worker '%s' because of worker sharing",
                         elts[i].key, elts[i].val, ap_proxy_worker_name(cmd->pool, worker));