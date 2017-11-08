static void ssl_scache_shmht_free(void *opt_param, void *ptr)
{
    SSLModConfigRec *mc = myModConfig((server_rec *)opt_param);

    apr_rmm_off_t off = apr_rmm_offset_get(mc->pSessionCacheDataRMM, ptr);
    apr_rmm_free(mc->pSessionCacheDataRMM, off);
    return;
}