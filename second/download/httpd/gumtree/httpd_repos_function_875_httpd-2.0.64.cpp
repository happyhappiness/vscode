void ssl_scache_expire(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_expire(s);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMHT)
        ssl_scache_shmht_expire(s);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        ssl_scache_shmcb_expire(s);
    return;
}