static void *ssl_scache_shmht_calloc(void *opt_param,
                                     size_t number, size_t size)
{
    SSLModConfigRec *mc = myModConfig((server_rec *)opt_param);

    apr_rmm_off_t off = apr_rmm_calloc(mc->pSessionCacheDataRMM, (number*size));

    return apr_rmm_addr_get(mc->pSessionCacheDataRMM, off);
}