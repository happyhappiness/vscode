static ipaddr_chain *new_ipaddr_chain(apr_pool_t *p,
                                      server_rec *s, server_addr_rec *sar)
{
    ipaddr_chain *new;

    new = apr_palloc(p, sizeof(*new));
    new->names = NULL;
    new->server = s;
    new->sar = sar;
    new->next = NULL;
    return new;
}