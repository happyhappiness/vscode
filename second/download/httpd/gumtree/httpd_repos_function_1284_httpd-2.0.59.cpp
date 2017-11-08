static void * merge_proxy_config(apr_pool_t *p, void *basev, void *overridesv)
{
    proxy_server_conf *ps = apr_pcalloc(p, sizeof(proxy_server_conf));
    proxy_server_conf *base = (proxy_server_conf *) basev;
    proxy_server_conf *overrides = (proxy_server_conf *) overridesv;

    ps->proxies = apr_array_append(p, base->proxies, overrides->proxies);
    ps->sec_proxy = apr_array_append(p, base->sec_proxy, overrides->sec_proxy);
    ps->aliases = apr_array_append(p, base->aliases, overrides->aliases);
    ps->raliases = apr_array_append(p, base->raliases, overrides->raliases);
    ps->noproxies = apr_array_append(p, base->noproxies, overrides->noproxies);
    ps->dirconn = apr_array_append(p, base->dirconn, overrides->dirconn);
    ps->allowed_connect_ports = apr_array_append(p, base->allowed_connect_ports, overrides->allowed_connect_ports);

    ps->domain = (overrides->domain == NULL) ? base->domain : overrides->domain;
    ps->viaopt = (overrides->viaopt_set == 0) ? base->viaopt : overrides->viaopt;
    ps->req = (overrides->req_set == 0) ? base->req : overrides->req;
    ps->recv_buffer_size = (overrides->recv_buffer_size_set == 0) ? base->recv_buffer_size : overrides->recv_buffer_size;
    ps->io_buffer_size = (overrides->io_buffer_size_set == 0) ? base->io_buffer_size : overrides->io_buffer_size;
    ps->maxfwd = (overrides->maxfwd_set == 0) ? base->maxfwd : overrides->maxfwd;
    ps->error_override = (overrides->error_override_set == 0) ? base->error_override : overrides->error_override;
    ps->preserve_host = (overrides->preserve_host_set == 0) ? base->preserve_host : overrides->preserve_host;
    ps->timeout= (overrides->timeout_set == 0) ? base->timeout : overrides->timeout;
    ps->badopt = (overrides->badopt_set == 0) ? base->badopt : overrides->badopt;

    return ps;
}