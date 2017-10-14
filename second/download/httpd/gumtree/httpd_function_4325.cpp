static void balancer_child_init(apr_pool_t *p, server_rec *s)
{
    while (s) {
        proxy_balancer *balancer;
        int i;
        void *sconf = s->module_config;
        proxy_server_conf *conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
        apr_status_t rv;

        if (conf->balancers->nelts) {
            apr_size_t size;
            unsigned int num;
            storage->attach(&(conf->bslot), conf->id, &size, &num, p);
            if (!conf->bslot) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01205) "slotmem_attach failed");
                exit(1); /* Ugly, but what else? */
            }
        }

        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
            rv = ap_proxy_initialize_balancer(balancer, s, p);

            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01206)
                             "Failed to init balancer %s in child",
                             balancer->s->name);
                exit(1); /* Ugly, but what else? */
            }
            init_balancer_members(conf->pool, s, balancer);
        }
        s = s->next;
    }

}