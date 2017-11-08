static int init_balancer_members(proxy_server_conf *conf, server_rec *s,
                                 proxy_balancer *balancer)
{
    int i;
    proxy_worker *workers;

    workers = (proxy_worker *)balancer->workers->elts;

    for (i = 0; i < balancer->workers->nelts; i++) {
        ap_proxy_initialize_worker_share(conf, workers, s);
        ap_proxy_initialize_worker(workers, s);
        ++workers;
    }

    workers = (proxy_worker *)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++) {
        /* Set to the original configuration */
        workers[i].s->lbstatus = workers[i].s->lbfactor =
          (workers[i].lbfactor ? workers[i].lbfactor : 1);
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