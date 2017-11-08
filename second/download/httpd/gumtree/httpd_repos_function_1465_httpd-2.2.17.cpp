static int init_balancer_members(proxy_server_conf *conf, server_rec *s,
                                 proxy_balancer *balancer)
{
    int i;
    proxy_worker *workers;
    int worker_is_initialized;
    proxy_worker_stat *slot;

    workers = (proxy_worker *)balancer->workers->elts;

    for (i = 0; i < balancer->workers->nelts; i++) {
        worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(workers);
        if (!worker_is_initialized) {
            /*
             * If the worker is not initialized check whether its scoreboard
             * slot is already initialized.
             */
            slot = (proxy_worker_stat *) ap_get_scoreboard_lb(workers->id);
            if (slot) {
                worker_is_initialized = slot->status & PROXY_WORKER_INITIALIZED;
            }
            else {
                worker_is_initialized = 0;
            }
        }
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