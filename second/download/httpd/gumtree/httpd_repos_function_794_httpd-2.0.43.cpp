static void *ssl_scache_shmht_realloc(void *opt_param, void *ptr, size_t size)
{
    SSLModConfigRec *mc = myModConfig((server_rec *)opt_param);

    apr_rmm_off_t off = apr_rmm_realloc(mc->pSessionCacheDataRMM, ptr, size);
    return apr_rmm_addr_get(mc->pSessionCacheDataRMM, off);
}