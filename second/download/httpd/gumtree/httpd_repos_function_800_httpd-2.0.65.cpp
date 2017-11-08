static void *ssl_scache_shmht_malloc(void *opt_param, size_t size)
{
    SSLModConfigRec *mc = myModConfig((server_rec *)opt_param);

    apr_rmm_off_t off = apr_rmm_calloc(mc->pSessionCacheDataRMM, size);
    return apr_rmm_addr_get(mc->pSessionCacheDataRMM, off);
}