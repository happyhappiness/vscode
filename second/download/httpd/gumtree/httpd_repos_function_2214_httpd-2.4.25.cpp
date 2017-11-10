static apr_status_t reset(proxy_balancer *balancer, server_rec *s)
{
    int i;
    proxy_worker **worker;
    worker = (proxy_worker **)balancer->workers->elts;
    for (i = 0; i < balancer->workers->nelts; i++, worker++) {
        (*worker)->s->lbstatus = 0;
    }
    return APR_SUCCESS;
}