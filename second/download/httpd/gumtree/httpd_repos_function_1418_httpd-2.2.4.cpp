static void recalc_factors(proxy_balancer *balancer)
{
    int i;
    proxy_worker *workers;


    /* Recalculate lbfactors */
    workers = (proxy_worker *)balancer->workers->elts;
    /* Special case if there is only one worker it's
     * load factor will always be 1
     */
    if (balancer->workers->nelts == 1) {
        workers->s->lbstatus = workers->s->lbfactor = 1;
        return;
    }
    for (i = 0; i < balancer->workers->nelts; i++) {
        /* Update the status entries */
        workers[i].s->lbstatus = workers[i].s->lbfactor;
    }
}