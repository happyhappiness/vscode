SSL_SESSION *ssl_scache_shmht_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *vp;
    SSL_SESSION *sess = NULL;
    UCHAR *ucpData;
    int nData;
    time_t expiry;
    time_t now;
    int n;

    /* allow the regular expiring to occur */
    ssl_scache_shmht_expire(s);

    /* lookup key in table */
    ssl_mutex_on(s);
    if (table_retrieve(mc->tSessionCacheDataTable,
                       id, idlen, &vp, &n) != TABLE_ERROR_NONE) {
        ssl_mutex_off(s);
        return NULL;
    }

    /* copy over the information to the SCI */
    nData = n-sizeof(time_t);
    ucpData = (UCHAR *)malloc(nData);
    if (ucpData == NULL) {
        ssl_mutex_off(s);
        return NULL;
    }
    memcpy(&expiry, vp, sizeof(time_t));
    memcpy(ucpData, (char *)vp+sizeof(time_t), nData);
    ssl_mutex_off(s);

    /* make sure the stuff is still not expired */
    now = time(NULL);
    if (expiry <= now) {
        ssl_scache_shmht_remove(s, id, idlen);
        return NULL;
    }

    /* unstreamed SSL_SESSION */
    sess = d2i_SSL_SESSION(NULL, &ucpData, nData);

    return sess;
}