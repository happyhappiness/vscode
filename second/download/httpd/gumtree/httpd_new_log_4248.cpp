ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01184) "Doing workers create: %s (%s), %d, %d",
                         balancer->s->name, balancer->s->sname,
                         (int)ALIGNED_PROXY_WORKER_SHARED_SIZE,
                         (int)balancer->max_workers);