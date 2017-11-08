SSLModConfigRec *ssl_config_global_create(server_rec *s)
{
    apr_pool_t *pool = s->process->pool;
    SSLModConfigRec *mc;
    void *vmc;

    apr_pool_userdata_get(&vmc, SSL_MOD_CONFIG_KEY, pool);
    if (vmc) {
        return vmc; /* reused for lifetime of the server */
    }

    /*
     * allocate an own subpool which survives server restarts
     */
    mc = (SSLModConfigRec *)apr_palloc(pool, sizeof(*mc));
    mc->pPool = pool;
    mc->bFixed = FALSE;

    /*
     * initialize per-module configuration
     */
    mc->nSessionCacheMode      = SSL_SCMODE_UNSET;
    mc->szSessionCacheDataFile = NULL;
    mc->nSessionCacheDataSize  = 0;
    mc->pSessionCacheDataMM    = NULL;
    mc->pSessionCacheDataRMM   = NULL;
    mc->tSessionCacheDataTable = NULL;
    mc->nMutexMode             = SSL_MUTEXMODE_UNSET;
    mc->nMutexMech             = APR_LOCK_DEFAULT;
    mc->szMutexFile            = NULL;
    mc->pMutex                 = NULL;
    mc->aRandSeed              = apr_array_make(pool, 4,
                                                sizeof(ssl_randseed_t));
    mc->tVHostKeys             = apr_hash_make(pool);
    mc->tPrivateKey            = apr_hash_make(pool);
    mc->tPublicCert            = apr_hash_make(pool);
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
    mc->szCryptoDevice         = NULL;
#endif

    memset(mc->pTmpKeys, 0, sizeof(mc->pTmpKeys));

    apr_pool_userdata_set(mc, SSL_MOD_CONFIG_KEY,
                          apr_pool_cleanup_null,
                          pool);

    return mc;
}