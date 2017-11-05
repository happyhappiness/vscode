ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02337)
                 "%s shm[%d] (0x%pp) for %s", action, i, (void *)shm,
                 balancer->s->name);