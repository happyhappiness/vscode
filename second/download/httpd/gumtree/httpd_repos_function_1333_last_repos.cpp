static void *create_server_config(apr_pool_t *p, server_rec *s)
{
    socache_mc_svr_cfg *sconf = apr_pcalloc(p, sizeof(socache_mc_svr_cfg));
    
    sconf->ttl = MC_DEFAULT_SERVER_TTL;

    return sconf;
}