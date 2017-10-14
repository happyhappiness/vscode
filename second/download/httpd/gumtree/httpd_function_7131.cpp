static int balancer_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                         apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    void *sconf = s->module_config;
    proxy_server_conf *conf;
    ap_slotmem_instance_t *new = NULL;
    apr_time_t tstamp;

    /* balancer_post_config() will be called twice during startup.  So, don't
     * set up the static data the 1st time through. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    if (!ap_proxy_retry_worker_fn) {
        ap_proxy_retry_worker_fn =
                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_retry_worker);
        if (!ap_proxy_retry_worker_fn) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02230)
                         "mod_proxy must be loaded for mod_proxy_balancer");
            return !OK;
        }
    }

    /*
     * Get slotmem setups
     */
    storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shm",
                                 AP_SLOTMEM_PROVIDER_VERSION);
    if (!storage) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01177)
                     "Failed to lookup provider 'shm' for '%s': is "
                     "mod_slotmem_shm loaded??",
                     AP_SLOTMEM_PROVIDER_GROUP);
        return !OK;
    }

    tstamp = apr_time_now();
    /*
     * Go thru each Vhost and create the shared mem slotmem for
     * each balancer's workers
     */
    while (s) {
        int i,j;
        proxy_balancer *balancer;
        sconf = s->module_config;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);

        if (conf->bslot) {
            /* Shared memory already created for this proxy_server_conf.
             */
            s = s->next;
            continue;
        }
        if (conf->balancers->nelts) {
            conf->max_balancers = conf->balancers->nelts + conf->bgrowth;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01178) "Doing balancers create: %d, %d (%d)",
                         (int)ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                         (int)conf->balancers->nelts, conf->max_balancers);

            rv = storage->create(&new, conf->id,
                                 ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                                 conf->max_balancers, AP_SLOTMEM_TYPE_PREGRAB, pconf);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01179) "balancer slotmem_create failed");
                return !OK;
            }
            conf->bslot = new;
        }
        conf->storage = storage;

        /* Initialize shared scoreboard data */
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
            proxy_worker **workers;
            proxy_worker *worker;
            proxy_balancer_shared *bshm;
            unsigned int index;

            balancer->max_workers = balancer->workers->nelts + balancer->growth;

            /* Create global mutex */
            rv = ap_global_mutex_create(&(balancer->gmutex), NULL, balancer_mutex_type,
                                        balancer->s->sname, s, pconf, 0);
            if (rv != APR_SUCCESS || !balancer->gmutex) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01180)
                             "mutex creation of %s : %s failed", balancer_mutex_type,
                             balancer->s->sname);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            apr_pool_cleanup_register(pconf, (void *)s, lock_remove,
                                      apr_pool_cleanup_null);

            /* setup shm for balancers */
            if ((rv = storage->grab(conf->bslot, &index)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01181) "balancer slotmem_grab failed");
                return !OK;

            }
            if ((rv = storage->dptr(conf->bslot, index, (void *)&bshm)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01182) "balancer slotmem_dptr failed");
                return !OK;
            }
            if ((rv = ap_proxy_share_balancer(balancer, bshm, index)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01183) "Cannot share balancer");
                return !OK;
            }

            /* create slotmem slots for workers */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01184) "Doing workers create: %s (%s), %d, %d",
                         balancer->s->name, balancer->s->sname,
                         (int)ALIGNED_PROXY_WORKER_SHARED_SIZE,
                         (int)balancer->max_workers);

            rv = storage->create(&new, balancer->s->sname,
                                 ALIGNED_PROXY_WORKER_SHARED_SIZE,
                                 balancer->max_workers, AP_SLOTMEM_TYPE_PREGRAB, pconf);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01185) "worker slotmem_create failed");
                return !OK;
            }
            balancer->wslot = new;
            balancer->storage = storage;

            /* sync all timestamps */
            balancer->wupdated = balancer->s->wupdated = tstamp;

            /* now go thru each worker */
            workers = (proxy_worker **)balancer->workers->elts;
            for (j = 0; j < balancer->workers->nelts; j++, workers++) {
                proxy_worker_shared *shm;

                worker = *workers;
                if ((rv = storage->grab(balancer->wslot, &index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01186) "worker slotmem_grab failed");
                    return !OK;

                }
                if ((rv = storage->dptr(balancer->wslot, index, (void *)&shm)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01187) "worker slotmem_dptr failed");
                    return !OK;
                }
                if ((rv = ap_proxy_share_worker(worker, shm, index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01188) "Cannot share worker");
                    return !OK;
                }
                worker->s->updated = tstamp;
            }
        }
        s = s->next;
    }

    return OK;
}