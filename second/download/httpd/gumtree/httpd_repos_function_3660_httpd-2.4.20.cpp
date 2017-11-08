static name_chain *new_name_chain(apr_pool_t *p,
                                  server_rec *s, server_addr_rec *sar)
{
    name_chain *new;

    new = apr_palloc(p, sizeof(*new));
    new->server = s;
    new->sar = sar;
    new->next = NULL;
    return new;
}