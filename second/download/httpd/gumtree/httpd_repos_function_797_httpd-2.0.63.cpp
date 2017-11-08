void ssl_scache_shmht_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->pSessionCacheDataRMM != NULL) {
        apr_rmm_destroy(mc->pSessionCacheDataRMM);
        mc->pSessionCacheDataRMM = NULL;
    }

    if (mc->pSessionCacheDataMM != NULL) {
        apr_shm_destroy(mc->pSessionCacheDataMM);
        mc->pSessionCacheDataMM = NULL;
    }
    return;
}