 * Create an already defined balancer and free up memory.
 */
PROXY_DECLARE(apr_status_t) ap_proxy_share_balancer(proxy_balancer *balancer,
                                                    proxy_balancer_shared *shm,
                                                    int i)
{
    proxy_balancer_method *lbmethod;
    if (!shm || !balancer->s)
        return APR_EINVAL;

    memcpy(shm, balancer->s, sizeof(proxy_balancer_shared));
    if (balancer->s->was_malloced)
        free(balancer->s);
    balancer->s = shm;
    balancer->s->index = i;
    /* the below should always succeed */
    lbmethod = ap_lookup_provider(PROXY_LBMETHOD, balancer->s->lbpname, "0");
    if (lbmethod)
        balancer->lbmethod = lbmethod;
    return APR_SUCCESS;
}

PROXY_DECLARE(apr_status_t) ap_proxy_initialize_balancer(proxy_balancer *balancer, server_rec *s, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    ap_slotmem_provider_t *storage = balancer->storage;
