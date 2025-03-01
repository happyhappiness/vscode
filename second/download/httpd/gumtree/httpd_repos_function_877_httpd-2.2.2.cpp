void ssl_scache_remove(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_remove(s, id, idlen);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        ssl_scache_shmcb_remove(s, id, idlen);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_remove(s, id, idlen);
#endif
    return;
}