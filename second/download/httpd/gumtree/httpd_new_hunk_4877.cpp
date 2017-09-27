    /*
     * Go thru each Vhost and create the shared mem slotmem for
     * each balancer's workers
     */
    while (s) {
        int i,j;
        char *id;
        proxy_balancer *balancer;
        ap_slotmem_type_t type;
        void *sconf = s->module_config;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
        /*
         * During create_proxy_config() we created a dummy id. Now that
         * we have identifying info, we can create the real id
         */
        id = apr_psprintf(pconf, "%s.%s.%d.%s.%s.%u.%s",
                          (s->server_scheme ? s->server_scheme : "????"),
                          (s->server_hostname ? s->server_hostname : "???"),
                          (int)s->port,
                          (s->server_admin ? s->server_admin : "??"),
                          (s->defn_name ? s->defn_name : "?"),
                          s->defn_line_number,
                          (s->error_fname ? s->error_fname : DEFAULT_ERRORLOG));
        conf->id = apr_psprintf(pconf, "p%x",
                                ap_proxy_hashfunc(id, PROXY_HASHFUNC_DEFAULT));
        if (conf->bslot) {
            /* Shared memory already created for this proxy_server_conf.
             */
            s = s->next;
            continue;
        }
        if (conf->bal_persist) {
            type = AP_SLOTMEM_TYPE_PREGRAB | AP_SLOTMEM_TYPE_PERSIST;
        } else {
            type = AP_SLOTMEM_TYPE_PREGRAB;
        }
        if (conf->balancers->nelts) {
            conf->max_balancers = conf->balancers->nelts + conf->bgrowth;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01178) "Doing balancers create: %d, %d (%d)",
                         (int)ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                         (int)conf->balancers->nelts, conf->max_balancers);

            rv = storage->create(&new, conf->id,
                                 ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                                 conf->max_balancers, type, pconf);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01179) "balancer slotmem_create failed");
                return !OK;
            }
            conf->bslot = new;
        }
