static void *create_server_config(apr_pool_t *p, server_rec *s)
{
    a_server_config *sconf = apr_palloc(p, sizeof(*sconf));

    sconf->fileht = apr_hash_make(p);
    return sconf;
}