}

static void force_recovery(proxy_balancer *balancer, server_rec *s)
{
    int i;
    int ok = 0;
    proxy_worker *worker;

    worker = (proxy_worker *)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++, worker++) {
        if (!(worker->s->status & PROXY_WORKER_IN_ERROR)) {
            ok = 1;
            break;
        }
        else {
            /* Try if we can recover */
            ap_proxy_retry_worker("BALANCER", worker, s);
            if (!(worker->s->status & PROXY_WORKER_IN_ERROR)) {
                ok = 1;
                break;
            }
        }
    }
    if (!ok && balancer->forcerecovery) {
        /* If all workers are in error state force the recovery.
         */
        worker = (proxy_worker *)balancer->workers->elts;
        for (i = 0; i < balancer->workers->nelts; i++, worker++) {
            ++worker->s->retries;
            worker->s->status &= ~PROXY_WORKER_IN_ERROR;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "proxy: BALANCER: (%s). Forcing recovery for worker (%s)",
                         balancer->name, worker->hostname);
        }
    }
}

static apr_status_t decrement_busy_count(void *worker_)
{
    proxy_worker *worker = worker_;
    
    if (worker->s->busy) {
        worker->s->busy--;
    }

    return APR_SUCCESS;
}

static int proxy_balancer_pre_request(proxy_worker **worker,
                                      proxy_balancer **balancer,
                                      request_rec *r,
                                      proxy_server_conf *conf, char **url)
{
    int access_status;
    proxy_worker *runtime;
    char *route = NULL;
    char *sticky = NULL;
    apr_status_t rv;

    *worker = NULL;
    /* Step 1: check if the url is for us
     * The url we can handle starts with 'balancer://'
     * If balancer is already provided skip the search
