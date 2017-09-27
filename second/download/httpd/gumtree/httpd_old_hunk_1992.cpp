    if ((*route) && (**route)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                  "proxy: BALANCER: Found route %s", *route);
        /* We have a route in path or in cookie
         * Find the worker that has this route defined.
         */
        worker = find_route_worker(balancer, *route);
        if (worker && !PROXY_WORKER_IS_USABLE(worker)) {
            /* We have a worker that is unusable.
             * It can be in error or disabled, but in case
             * it has a redirection set use that redirection worker.
             * This enables to safely remove the member from the
             * balancer. Of course you will need a some kind of
             * session replication between those two remote.
             */
            if (*worker->s->redirect)
                worker = find_route_worker(balancer, worker->s->redirect);
            /* Check if the redirect worker is usable */
            if (worker && !PROXY_WORKER_IS_USABLE(worker))
                worker = NULL;
        }
        return worker;
    }
    else
        return NULL;
}

static proxy_worker *find_best_worker(proxy_balancer *balancer,
                                      request_rec *r)
{
    proxy_worker *candidate = NULL;

    if (PROXY_THREAD_LOCK(balancer) != APR_SUCCESS)
        return NULL;

    candidate = (*balancer->lbmethod->finder)(balancer, r);

/*
        PROXY_THREAD_UNLOCK(balancer);
        return NULL;
*/

    PROXY_THREAD_UNLOCK(balancer);

    if (candidate == NULL) {
        /* All the workers are in error state or disabled.
         * If the balancer has a timeout sleep for a while
         * and try again to find the worker. The chances are
         * that some other thread will release a connection.
