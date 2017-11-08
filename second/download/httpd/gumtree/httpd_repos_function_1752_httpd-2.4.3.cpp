static proxy_worker *find_best_worker(proxy_balancer *balancer,
                                      request_rec *r)
{
    proxy_worker *candidate = NULL;
    apr_status_t rv;

    if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01163)
                      "%s: Lock failed for find_best_worker()",
                      balancer->s->name);
        return NULL;
    }

    candidate = (*balancer->lbmethod->finder)(balancer, r);

    if (candidate)
        candidate->s->elected++;

    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01164)
                      "%s: Unlock failed for find_best_worker()",
                      balancer->s->name);
    }

    if (candidate == NULL) {
        /* All the workers are in error state or disabled.
         * If the balancer has a timeout sleep for a while
         * and try again to find the worker. The chances are
         * that some other thread will release a connection.
         * By default the timeout is not set, and the server
         * returns SERVER_BUSY.
         */
        if (balancer->s->timeout) {
            /* XXX: This can perhaps be build using some
             * smarter mechanism, like tread_cond.
             * But since the statuses can came from
             * different childs, use the provided algo.
             */
            apr_interval_time_t timeout = balancer->s->timeout;
            apr_interval_time_t step, tval = 0;
            /* Set the timeout to 0 so that we don't
             * end in infinite loop
             */
            balancer->s->timeout = 0;
            step = timeout / 100;
            while (tval < timeout) {
                apr_sleep(step);
                /* Try again */
                if ((candidate = find_best_worker(balancer, r)))
                    break;
                tval += step;
            }
            /* restore the timeout */
            balancer->s->timeout = timeout;
        }
    }

    return candidate;

}