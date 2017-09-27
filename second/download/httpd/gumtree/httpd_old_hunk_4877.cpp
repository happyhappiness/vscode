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
