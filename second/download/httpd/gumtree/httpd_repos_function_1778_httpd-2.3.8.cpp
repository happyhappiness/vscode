static void child_init(apr_pool_t *p, server_rec *s)
{
    proxy_worker *reverse = NULL;

    while (s) {
        void *sconf = s->module_config;
        proxy_server_conf *conf;
        proxy_worker *worker;
        int i;

        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
        /* Initialize worker's shared scoreboard data */
        worker = (proxy_worker *)conf->workers->elts;
        for (i = 0; i < conf->workers->nelts; i++) {
            ap_proxy_initialize_worker_share(conf, worker, s);
            ap_proxy_initialize_worker(worker, s, p);
            worker++;
        }
        /* Create and initialize forward worker if defined */
        if (conf->req_set && conf->req) {
            conf->forward = ap_proxy_create_worker(p);
            conf->forward->name     = "proxy:forward";
            conf->forward->hostname = "*";
            conf->forward->scheme   = "*";
            ap_proxy_initialize_worker_share(conf, conf->forward, s);
            ap_proxy_initialize_worker(conf->forward, s, p);
            /* Do not disable worker in case of errors */
            conf->forward->s->status |= PROXY_WORKER_IGNORE_ERRORS;
            /* Disable address cache for generic forward worker */
            conf->forward->is_address_reusable = 0;
        }
        if (!reverse) {
            reverse = ap_proxy_create_worker(p);
            reverse->name     = "proxy:reverse";
            reverse->hostname = "*";
            reverse->scheme   = "*";
            ap_proxy_initialize_worker_share(conf, reverse, s);
            ap_proxy_initialize_worker(reverse, s, p);
            /* Do not disable worker in case of errors */
            reverse->s->status |= PROXY_WORKER_IGNORE_ERRORS;
            /* Disable address cache for generic reverse worker */
            reverse->is_address_reusable = 0;
        }
        conf->reverse = reverse;
        s = s->next;
    }
}