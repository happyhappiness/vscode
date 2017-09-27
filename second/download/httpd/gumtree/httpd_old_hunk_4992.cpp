}

static void child_init(apr_pool_t *p, server_rec *s)
{
    proxy_worker *reverse = NULL;

    /* TODO */
    while (s) {
        void *sconf = s->module_config;
        proxy_server_conf *conf;
        proxy_worker *worker;
        int i;
