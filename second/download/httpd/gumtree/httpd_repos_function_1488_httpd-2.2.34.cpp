static int init_balancer_members(proxy_server_conf *conf, server_rec *s,
                                 proxy_balancer *balancer)
{
    int i;
    proxy_worker *workers;
    int worker_is_initialized;

    workers = (proxy_worker *)balancer->workers->elts;

    for (i = 0; i < balancer->workers->nelts; i++) {
        worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(workers);
#if PROXY_HAS_SCOREBOARD
        /*
         * If the worker is not initialized but has a scoreboard
         * slot, check whether it was already initialized in a
         * previous generation to avoid resetting the shared lb
         * parameters below.
         */
        if (!worker_is_initialized) {
            ap_proxy_set_scoreboard_lb(workers, balancer, s);
            worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(workers);
        }
#endif
        ap_proxy_initialize_worker_share(conf, workers, s);
        ap_proxy_initialize_worker(workers, s);
        if (!worker_is_initialized) {
            /* Set to the original configuration */
            workers->s->lbstatus = workers->s->lbfactor =
            (workers->lbfactor ? workers->lbfactor : 1);
            workers->s->lbset = workers->lbset;
        }
        ++workers;
    }

    /* Set default number of attempts to the number of
     * workers.
     */
    if (!balancer->max_attempts_set && balancer->workers->nelts > 1) {
        balancer->max_attempts = balancer->workers->nelts - 1;
        balancer->max_attempts_set = 1;
    }
    return 0;
}