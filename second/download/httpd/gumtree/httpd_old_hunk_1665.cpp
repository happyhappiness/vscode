    if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
            "proxy: BALANCER: (%s). Lock failed for post_request",
            balancer->name);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (!apr_is_empty_array(balancer->errstatuses)) {
        int i;
        for (i = 0; i < balancer->errstatuses->nelts; i++) {
            int val = ((int *)balancer->errstatuses->elts)[i];
            if (r->status == val) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                             "proxy: BALANCER: (%s).  Forcing worker (%s) into error state "
                             "due to status code %d matching 'failonstatus' "
                             "balancer parameter",
                             balancer->name, worker->name, val);
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                worker->s->error_time = apr_time_now();
                break;
            }
        }
    }

    if (balancer->failontimeout
        && (apr_table_get(r->notes, "proxy_timedout")) != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "%s: Forcing worker (%s) into error state "
                      "due to timeout and 'failonstatus' parameter being set",
                       balancer->name, worker->name);
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        worker->s->error_time = apr_time_now();

    }

    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
            "proxy: BALANCER: (%s). Unlock failed for post_request",
            balancer->name);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy_balancer_post_request for (%s)", balancer->name);

    return OK;
}

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

/* post_config hook: */
static int balancer_init(apr_pool_t *p, apr_pool_t *plog,
                         apr_pool_t *ptemp, server_rec *s)
{
    void *data;
    const char *userdata_key = "mod_proxy_balancer_init";
    apr_uuid_t uuid;

    /* balancer_init() will be called twice during startup.  So, only
     * set up the static data the second time through. */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);
        return OK;
    }

    /* Retrieve a UUID and store the nonce for the lifetime of
     * the process. */
    apr_uuid_get(&uuid);
    apr_uuid_format(balancer_nonce, &uuid);

    return OK;
}

/* Manages the loadfactors and member status
 */
static int balancer_handler(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf = (proxy_server_conf *)
        ap_get_module_config(sconf, &proxy_module);
    proxy_balancer *balancer, *bsel = NULL;
    proxy_worker *worker, *wsel = NULL;
    apr_table_t *params = apr_table_make(r->pool, 10);
    int access_status;
    int i, n;
    const char *name;

    /* is this for us? */
