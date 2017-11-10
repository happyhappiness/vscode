static apr_status_t lock_remove(void *data)
{
    int i;
    proxy_balancer *balancer;
    server_rec *s = data;
    void *sconf = s->module_config;
    proxy_server_conf *conf = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    balancer = (proxy_balancer *)conf->balancers->elts;
    for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
        if (balancer->gmutex) {
            apr_global_mutex_destroy(balancer->gmutex);
            balancer->gmutex = NULL;
        }
    }
    return(0);
}