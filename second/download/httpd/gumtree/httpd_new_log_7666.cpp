ap_log_error(APLOG_MARK, APLOG_INFO, 0, cmd->server, APLOGNO(01145)
                         "Sharing worker '%s' instead of creating new worker '%s'",
                         ap_proxy_worker_name(cmd->pool, worker), new->real);