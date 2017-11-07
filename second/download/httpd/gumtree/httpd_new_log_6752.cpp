ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01148)
                     "Defined worker '%s' for balancer '%s'",
                     ap_proxy_worker_name(cmd->pool, worker), balancer->s->name);