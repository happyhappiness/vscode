static void child_init(apr_pool_t *p, server_rec *s)
{
    while (s) {
        void *sconf = s->module_config;
        proxy_server_conf *conf;
        proxy_balancer *balancer;
        int i;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);

        /* Initialize shared scoreboard data */
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            if (balancer->lbmethod && balancer->lbmethod->reset)
               balancer->lbmethod->reset(balancer, s);
            init_balancer_members(conf, s, balancer);
            balancer++;
        }
        s = s->next;
    }

}