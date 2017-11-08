void ssl_scache_dbm_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_pool_t *p;

    apr_pool_sub_make(&p, mc->pPool, NULL);
    if (p != NULL) {
        /* the correct way */
        unlink(apr_pstrcat(p, mc->szSessionCacheDataFile, SSL_DBM_FILE_SUFFIX_DIR, NULL));
        unlink(apr_pstrcat(p, mc->szSessionCacheDataFile, SSL_DBM_FILE_SUFFIX_PAG, NULL));
        /* the additional ways to be sure */
        unlink(apr_pstrcat(p, mc->szSessionCacheDataFile, ".dir", NULL));
        unlink(apr_pstrcat(p, mc->szSessionCacheDataFile, ".pag", NULL));
        unlink(apr_pstrcat(p, mc->szSessionCacheDataFile, ".db", NULL));
        unlink(mc->szSessionCacheDataFile);
        apr_pool_destroy(p);
    }
    return;
}