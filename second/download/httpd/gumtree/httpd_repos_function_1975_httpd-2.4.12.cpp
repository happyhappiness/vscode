static void * merge_proxy_config(apr_pool_t *p, void *basev, void *overridesv)
{
    proxy_server_conf *ps = apr_pcalloc(p, sizeof(proxy_server_conf));
    proxy_server_conf *base = (proxy_server_conf *) basev;
    proxy_server_conf *overrides = (proxy_server_conf *) overridesv;

    ps->inherit = (overrides->inherit_set == 0) ? base->inherit : overrides->inherit;
    ps->inherit_set = overrides->inherit_set || base->inherit_set;

    ps->ppinherit = (overrides->ppinherit_set == 0) ? base->ppinherit : overrides->ppinherit;
    ps->ppinherit_set = overrides->ppinherit_set || base->ppinherit_set;

    if (ps->ppinherit) {
        ps->proxies = apr_array_append(p, base->proxies, overrides->proxies);
    }
    else {
        ps->proxies = overrides->proxies;
    }
    ps->sec_proxy = apr_array_append(p, base->sec_proxy, overrides->sec_proxy);
    ps->aliases = apr_array_append(p, base->aliases, overrides->aliases);
    ps->noproxies = apr_array_append(p, base->noproxies, overrides->noproxies);
    ps->dirconn = apr_array_append(p, base->dirconn, overrides->dirconn);
    if (ps->inherit || ps->ppinherit) {
        ps->workers = apr_array_append(p, base->workers, overrides->workers);
        ps->balancers = apr_array_append(p, base->balancers, overrides->balancers);
    }
    else {
        ps->workers = overrides->workers;
        ps->balancers = overrides->balancers;
    }
    ps->forward = overrides->forward ? overrides->forward : base->forward;
    ps->reverse = overrides->reverse ? overrides->reverse : base->reverse;

    ps->domain = (overrides->domain == NULL) ? base->domain : overrides->domain;
    ps->id = (overrides->id == NULL) ? base->id : overrides->id;
    ps->viaopt = (overrides->viaopt_set == 0) ? base->viaopt : overrides->viaopt;
    ps->viaopt_set = overrides->viaopt_set || base->viaopt_set;
    ps->req = (overrides->req_set == 0) ? base->req : overrides->req;
    ps->req_set = overrides->req_set || base->req_set;
    ps->bgrowth = (overrides->bgrowth_set == 0) ? base->bgrowth : overrides->bgrowth;
    ps->bgrowth_set = overrides->bgrowth_set || base->bgrowth_set;
    ps->max_balancers = overrides->max_balancers || base->max_balancers;
    ps->bal_persist = overrides->bal_persist;
    ps->recv_buffer_size = (overrides->recv_buffer_size_set == 0) ? base->recv_buffer_size : overrides->recv_buffer_size;
    ps->recv_buffer_size_set = overrides->recv_buffer_size_set || base->recv_buffer_size_set;
    ps->io_buffer_size = (overrides->io_buffer_size_set == 0) ? base->io_buffer_size : overrides->io_buffer_size;
    ps->io_buffer_size_set = overrides->io_buffer_size_set || base->io_buffer_size_set;
    ps->maxfwd = (overrides->maxfwd_set == 0) ? base->maxfwd : overrides->maxfwd;
    ps->maxfwd_set = overrides->maxfwd_set || base->maxfwd_set;
    ps->timeout = (overrides->timeout_set == 0) ? base->timeout : overrides->timeout;
    ps->timeout_set = overrides->timeout_set || base->timeout_set;
    ps->badopt = (overrides->badopt_set == 0) ? base->badopt : overrides->badopt;
    ps->badopt_set = overrides->badopt_set || base->badopt_set;
    ps->proxy_status = (overrides->proxy_status_set == 0) ? base->proxy_status : overrides->proxy_status;
    ps->proxy_status_set = overrides->proxy_status_set || base->proxy_status_set;
    ps->source_address = (overrides->source_address_set == 0) ? base->source_address : overrides->source_address;
    ps->source_address_set = overrides->source_address_set || base->source_address_set;
    ps->pool = base->pool;
    return ps;
}