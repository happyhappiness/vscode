static void * create_proxy_config(apr_pool_t *p, server_rec *s)
{
    proxy_server_conf *ps = apr_pcalloc(p, sizeof(proxy_server_conf));

    ps->sec_proxy = apr_array_make(p, 10, sizeof(ap_conf_vector_t *));
    ps->proxies = apr_array_make(p, 10, sizeof(struct proxy_remote));
    ps->aliases = apr_array_make(p, 10, sizeof(struct proxy_alias));
    ps->noproxies = apr_array_make(p, 10, sizeof(struct noproxy_entry));
    ps->dirconn = apr_array_make(p, 10, sizeof(struct dirconn_entry));
    ps->workers = apr_array_make(p, 10, sizeof(proxy_worker));
    ps->balancers = apr_array_make(p, 10, sizeof(proxy_balancer));
    ps->forward = NULL;
    ps->reverse = NULL;
    ps->domain = NULL;
    ps->id = apr_psprintf(p, "p%x", 1); /* simply for storage size */
    ps->viaopt = via_off; /* initially backward compatible with 1.3.1 */
    ps->viaopt_set = 0; /* 0 means default */
    ps->req = 0;
    ps->max_balancers = 0;
    ps->bal_persist = 0;
    ps->inherit = 1;
    ps->inherit_set = 0;
    ps->ppinherit = 1;
    ps->ppinherit_set = 0;
    ps->bgrowth = 5;
    ps->bgrowth_set = 0;
    ps->req_set = 0;
    ps->recv_buffer_size = 0; /* this default was left unset for some reason */
    ps->recv_buffer_size_set = 0;
    ps->io_buffer_size = AP_IOBUFSIZE;
    ps->io_buffer_size_set = 0;
    ps->maxfwd = DEFAULT_MAX_FORWARDS;
    ps->maxfwd_set = 0;
    ps->timeout = 0;
    ps->timeout_set = 0;
    ps->badopt = bad_error;
    ps->badopt_set = 0;
    ps->source_address = NULL;
    ps->source_address_set = 0;
    apr_pool_create_ex(&ps->pool, p, NULL, NULL);

    return ps;
}