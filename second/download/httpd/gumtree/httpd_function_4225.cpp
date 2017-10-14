static void force_recovery(proxy_balancer *balancer, server_rec *s)
{
    int i;
    int ok = 0;
    proxy_worker **worker;

    worker = (proxy_worker **)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++, worker++) {
        if (!((*worker)->s->status & PROXY_WORKER_IN_ERROR)) {
            ok = 1;
            break;
        }
        else {
            /* Try if we can recover */
            ap_proxy_retry_worker("BALANCER", *worker, s);
            if (!((*worker)->s->status & PROXY_WORKER_IN_ERROR)) {
                ok = 1;
                break;
            }
        }
    }
    if (!ok) {
        /* If all workers are in error state force the recovery.
         */
        worker = (proxy_worker **)balancer->workers->elts;
        for (i = 0; i < balancer->workers->nelts; i++, worker++) {
            ++(*worker)->s->retries;
            (*worker)->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: BALANCER: (%s). Forcing recovery for worker (%s)",
                         balancer->name, (*worker)->hostname);
        }
    }
}