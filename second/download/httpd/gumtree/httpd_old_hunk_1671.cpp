        int i;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);

        /* Initialize shared scoreboard data */
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            init_balancer_members(conf, s, balancer);
            balancer++;
        }
        s = s->next;
    }

}

/*
 * The idea behind the find_best_byrequests scheduler is the following:
 *
 * lbfactor is "how much we expect this worker to work", or "the worker's
 * normalized work quota".
 *
 * lbstatus is "how urgent this worker has to work to fulfill its quota
 * of work".
 *
 * We distribute each worker's work quota to the worker, and then look
 * which of them needs to work most urgently (biggest lbstatus).  This
 * worker is then selected for work, and its lbstatus reduced by the
 * total work quota we distributed to all workers.  Thus the sum of all
 * lbstatus does not change.(*)
 *
 * If some workers are disabled, the others will
 * still be scheduled correctly.
 *
 * If a balancer is configured as follows:
 *
 * worker     a    b    c    d
 * lbfactor  25   25   25   25
 *
 * And b gets disabled, the following schedule is produced:
 *
 *    a c d a c d a c d ...
 *
 * Note that the above lbfactor setting is the *exact* same as:
 *
 * worker     a    b    c    d
 * lbfactor   1    1    1    1
 *
 * Asymmetric configurations work as one would expect. For
 * example:
 *
 * worker     a    b    c    d
 * lbfactor   1    1    1    2
 *
 * would have a, b and c all handling about the same
 * amount of load with d handling twice what a or b
 * or c handles individually. So we could see:
 *
 *   b a d c d a c d b d ...
 *
 */

static proxy_worker *find_best_byrequests(proxy_balancer *balancer,
                                request_rec *r)
{
    int i;
    int total_factor = 0;
    proxy_worker *worker;
    proxy_worker *mycandidate = NULL;
    int cur_lbset = 0;
    int max_lbset = 0;
    int checking_standby;
    int checked_standby;
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering byrequests for BALANCER (%s)",
                 balancer->name);

    /* First try to see if we have available candidate */
    do {
        checking_standby = checked_standby = 0;
        while (!mycandidate && !checked_standby) {
            worker = (proxy_worker *)balancer->workers->elts;
            for (i = 0; i < balancer->workers->nelts; i++, worker++) {
                if (!checking_standby) {    /* first time through */
                    if (worker->s->lbset > max_lbset)
                        max_lbset = worker->s->lbset;
                }
                if (worker->s->lbset != cur_lbset)
                    continue;
                if ( (checking_standby ? !PROXY_WORKER_IS_STANDBY(worker) : PROXY_WORKER_IS_STANDBY(worker)) )
                    continue;
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
                    worker->s->lbstatus += worker->s->lbfactor;
                    total_factor += worker->s->lbfactor;
                    if (!mycandidate || worker->s->lbstatus > mycandidate->s->lbstatus)
                        mycandidate = worker;
                }
            }
            checked_standby = checking_standby++;
        }
        cur_lbset++;
    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        mycandidate->s->lbstatus -= total_factor;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: byrequests selected worker \"%s\" : busy %" APR_SIZE_T_FMT " : lbstatus %d",
                     mycandidate->name, mycandidate->s->busy, mycandidate->s->lbstatus);

    }

    return mycandidate;
}

/*
 * The idea behind the find_best_bytraffic scheduler is the following:
 *
 * We know the amount of traffic (bytes in and out) handled by each
 * worker. We normalize that traffic by each workers' weight. So assuming
 * a setup as below:
 *
 * worker     a    b    c
 * lbfactor   1    1    3
 *
 * the scheduler will allow worker c to handle 3 times the
 * traffic of a and b. If each request/response results in the
 * same amount of traffic, then c would be accessed 3 times as
 * often as a or b. If, for example, a handled a request that
 * resulted in a large i/o bytecount, then b and c would be
 * chosen more often, to even things out.
 */
static proxy_worker *find_best_bytraffic(proxy_balancer *balancer,
                                         request_rec *r)
{
    int i;
    apr_off_t mytraffic = 0;
    apr_off_t curmin = 0;
    proxy_worker *worker;
    proxy_worker *mycandidate = NULL;
    int cur_lbset = 0;
    int max_lbset = 0;
    int checking_standby;
    int checked_standby;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering bytraffic for BALANCER (%s)",
                 balancer->name);

    /* First try to see if we have available candidate */
    do {
        checking_standby = checked_standby = 0;
        while (!mycandidate && !checked_standby) {
            worker = (proxy_worker *)balancer->workers->elts;
            for (i = 0; i < balancer->workers->nelts; i++, worker++) {
                if (!checking_standby) {    /* first time through */
                    if (worker->s->lbset > max_lbset)
                        max_lbset = worker->s->lbset;
                }
                if (worker->s->lbset != cur_lbset)
                    continue;
                if ( (checking_standby ? !PROXY_WORKER_IS_STANDBY(worker) : PROXY_WORKER_IS_STANDBY(worker)) )
                    continue;
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
            }
            checked_standby = checking_standby++;
        }
        cur_lbset++;
    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: bytraffic selected worker \"%s\" : busy %" APR_SIZE_T_FMT,
                     mycandidate->name, mycandidate->s->busy);

    }

    return mycandidate;
}

static proxy_worker *find_best_bybusyness(proxy_balancer *balancer,
                                request_rec *r)
{

    int i;
    proxy_worker *worker;
    proxy_worker *mycandidate = NULL;
    int cur_lbset = 0;
    int max_lbset = 0;
    int checking_standby;
    int checked_standby;

    int total_factor = 0;
    
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy: Entering bybusyness for BALANCER (%s)",
                 balancer->name);

    /* First try to see if we have available candidate */
    do {

        checking_standby = checked_standby = 0;
        while (!mycandidate && !checked_standby) {

            worker = (proxy_worker *)balancer->workers->elts;
            for (i = 0; i < balancer->workers->nelts; i++, worker++) {
                if  (!checking_standby) {    /* first time through */
                    if (worker->s->lbset > max_lbset)
                        max_lbset = worker->s->lbset;
                }

                if (worker->s->lbset != cur_lbset)
                    continue;

                if ( (checking_standby ? !PROXY_WORKER_IS_STANDBY(worker) : PROXY_WORKER_IS_STANDBY(worker)) )
                    continue;

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

                    worker->s->lbstatus += worker->s->lbfactor;
                    total_factor += worker->s->lbfactor;
                    
                    if (!mycandidate
                        || worker->s->busy < mycandidate->s->busy
                        || (worker->s->busy == mycandidate->s->busy && worker->s->lbstatus > mycandidate->s->lbstatus))
                        mycandidate = worker;

                }

            }

            checked_standby = checking_standby++;

        }

        cur_lbset++;

    } while (cur_lbset <= max_lbset && !mycandidate);

    if (mycandidate) {
        mycandidate->s->lbstatus -= total_factor;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: bybusyness selected worker \"%s\" : busy %" APR_SIZE_T_FMT " : lbstatus %d",
                     mycandidate->name, mycandidate->s->busy, mycandidate->s->lbstatus);

    }

    return mycandidate;

}

/*
 * How to add additional lbmethods:
 *   1. Create func which determines "best" candidate worker
 *      (eg: find_best_bytraffic, above)
 *   2. Register it as a provider.
 */
static const proxy_balancer_method byrequests =
{
    "byrequests",
    &find_best_byrequests,
    NULL
};

static const proxy_balancer_method bytraffic =
{
    "bytraffic",
    &find_best_bytraffic,
    NULL
};

static const proxy_balancer_method bybusyness =
{
    "bybusyness",
    &find_best_bybusyness,
    NULL
};


static void ap_proxy_balancer_register_hook(apr_pool_t *p)
{
    /* Only the mpm_winnt has child init hook handler.
     * make sure that we are called after the mpm
     * initializes and after the mod_proxy
     */
    static const char *const aszPred[] = { "mpm_winnt.c", "mod_proxy.c", NULL};
     /* manager handler */
    ap_hook_post_config(balancer_init, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(balancer_handler, NULL, NULL, APR_HOOK_FIRST);
    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);
    proxy_hook_pre_request(proxy_balancer_pre_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_post_request(proxy_balancer_post_request, NULL, NULL, APR_HOOK_FIRST);
    proxy_hook_canon_handler(proxy_balancer_canon, NULL, NULL, APR_HOOK_FIRST);
    ap_register_provider(p, PROXY_LBMETHOD, "bytraffic", "0", &bytraffic);
    ap_register_provider(p, PROXY_LBMETHOD, "byrequests", "0", &byrequests);
    ap_register_provider(p, PROXY_LBMETHOD, "bybusyness", "0", &bybusyness);
}

module AP_MODULE_DECLARE_DATA proxy_balancer_module = {
    STANDARD20_MODULE_STUFF,
    NULL,       /* create per-directory config structure */
    NULL,       /* merge per-directory config structures */
    NULL,       /* create per-server config structure */
    NULL,       /* merge per-server config structures */
    NULL,       /* command apr_table_t */
    ap_proxy_balancer_register_hook /* register hooks */
};
