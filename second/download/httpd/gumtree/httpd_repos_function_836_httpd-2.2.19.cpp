void ssl_scache_shmcb_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->pSessionCacheDataMM != NULL) {
        apr_shm_destroy(mc->pSessionCacheDataMM);
        mc->pSessionCacheDataMM = NULL;
    }
    return;
}