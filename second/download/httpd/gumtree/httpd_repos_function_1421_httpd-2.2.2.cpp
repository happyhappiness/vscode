static proxy_worker *find_best_bytraffic(proxy_balancer *balancer,
                                         request_rec *r)
{
    int i;
    apr_off_t mytraffic = 0;
    apr_off_t curmin = 0;
    proxy_worker *worker = (proxy_worker *)balancer->workers->elts;
    proxy_worker *mycandidate = NULL;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering bytraffic for BALANCER (%s)",
                 balancer->name);

    /* First try to see if we have available candidate */
    for (i = 0; i < balancer->workers->nelts; i++) {
        /* If the worker is in error state run
         * retry on that worker. It will be marked as
         * operational if the retry timeout is elapsed.
         * The worker might still be unusable, but we try
         * anyway.
         */
        if (!PROXY_WORKER_IS_USABLE(worker))
            ap_proxy_retry_worker("BALANCER", worker, r->server);
        /* Take into calculation only the workers that are
         * not in error state or not disabled.
         */
        if (PROXY_WORKER_IS_USABLE(worker)) {
            mytraffic = (worker->s->transferred/worker->s->lbfactor) +
                        (worker->s->read/worker->s->lbfactor);
            if (!mycandidate || mytraffic < curmin) {
                mycandidate = worker;
                curmin = mytraffic;
            }
        }
        worker++;
    }

    if (mycandidate) {
        mycandidate->s->elected++;
    }

    return mycandidate;
}