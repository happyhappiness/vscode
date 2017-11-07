static void child_init(apr_pool_t *p, server_rec *s)
{
    proxy_worker *reverse = NULL;

    apr_status_t rv = apr_global_mutex_child_init(&proxy_mutex,
                                      apr_global_mutex_lockfile(proxy_mutex),
                                      p);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02479)
                     "could not init proxy_mutex in child");
        exit(1); /* Ugly, but what else? */
    }

    /* TODO */
    while (s) {
        void *sconf = s->module_config;
        proxy_server_conf *conf;
        proxy_worker *worker;
        int i;

        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
        /*
         * NOTE: non-balancer members don't use shm at all...
         *       after all, why should they?
         */
        worker = (proxy_worker *)conf->workers->elts;
        for (i = 0; i < conf->workers->nelts; i++, worker++) {
            ap_proxy_initialize_worker(worker, s, conf->pool);
        }
        /* Create and initialize forward worker if defined */
        if (conf->req_set && conf->req) {
            proxy_worker *forward;
            ap_proxy_define_worker(p, &forward, NULL, NULL, "http://www.apache.org", 0);
            conf->forward = forward;
            PROXY_STRNCPY(conf->forward->s->name,     "proxy:forward");
            PROXY_STRNCPY(conf->forward->s->hostname, "*");
            PROXY_STRNCPY(conf->forward->s->scheme,   "*");
            conf->forward->hash.def = conf->forward->s->hash.def =
                ap_proxy_hashfunc(conf->forward->s->name, PROXY_HASHFUNC_DEFAULT);
             conf->forward->hash.fnv = conf->forward->s->hash.fnv =
                ap_proxy_hashfunc(conf->forward->s->name, PROXY_HASHFUNC_FNV);
            /* Do not disable worker in case of errors */
            conf->forward->s->status |= PROXY_WORKER_IGNORE_ERRORS;
            ap_proxy_initialize_worker(conf->forward, s, conf->pool);
            /* Disable address cache for generic forward worker */
            conf->forward->s->is_address_reusable = 0;
        }
        if (!reverse) {
            ap_proxy_define_worker(p, &reverse, NULL, NULL, "http://www.apache.org", 0);
            PROXY_STRNCPY(reverse->s->name,     "proxy:reverse");
            PROXY_STRNCPY(reverse->s->hostname, "*");
            PROXY_STRNCPY(reverse->s->scheme,   "*");
            reverse->hash.def = reverse->s->hash.def =
                ap_proxy_hashfunc(reverse->s->name, PROXY_HASHFUNC_DEFAULT);
            reverse->hash.fnv = reverse->s->hash.fnv =
                ap_proxy_hashfunc(reverse->s->name, PROXY_HASHFUNC_FNV);
            /* Do not disable worker in case of errors */
            reverse->s->status |= PROXY_WORKER_IGNORE_ERRORS;
            conf->reverse = reverse;
            ap_proxy_initialize_worker(conf->reverse, s, conf->pool);
            /* Disable address cache for generic reverse worker */
            reverse->s->is_address_reusable = 0;
        }
        conf->reverse = reverse;
        s = s->next;
    }
}