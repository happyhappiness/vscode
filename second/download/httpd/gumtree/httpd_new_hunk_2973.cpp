        /* If all workers are in error state force the recovery.
         */
        worker = (proxy_worker **)balancer->workers->elts;
        for (i = 0; i < balancer->workers->nelts; i++, worker++) {
            ++(*worker)->s->retries;
            (*worker)->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01165)
                         "%s: Forcing recovery for worker (%s)",
                         balancer->s->name, (*worker)->s->hostname);
        }
    }
}

static int proxy_balancer_pre_request(proxy_worker **worker,
                                      proxy_balancer **balancer,
