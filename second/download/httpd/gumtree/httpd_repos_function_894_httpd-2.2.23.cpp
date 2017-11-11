BOOL ssl_scache_store(server_rec *s, UCHAR *id, int idlen, time_t expiry, SSL_SESSION *sess)
{
    SSLModConfigRec *mc = myModConfig(s);
    BOOL rv = FALSE;

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        rv = ssl_scache_dbm_store(s, id, idlen, expiry, sess);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        rv = ssl_scache_shmcb_store(s, id, idlen, expiry, sess);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        rv = ssl_scache_dc_store(s, id, idlen, expiry, sess);
#endif
    return rv;
}