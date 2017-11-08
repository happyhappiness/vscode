BOOL ssl_scache_shmht_store(server_rec *s, UCHAR *id, int idlen, time_t expiry, SSL_SESSION *sess)
{
    SSLModConfigRec *mc = myModConfig(s);
    void *vp;
    UCHAR ucaData[SSL_SESSION_MAX_DER];
    int nData;
    UCHAR *ucp;

    /* streamline session data */
    if ((nData = i2d_SSL_SESSION(sess, NULL)) > sizeof(ucaData))
        return FALSE;
    ucp = ucaData;
    i2d_SSL_SESSION(sess, &ucp);

    ssl_mutex_on(s);
    if (table_insert_kd(mc->tSessionCacheDataTable, 
                        id, idlen, NULL, sizeof(time_t)+nData,
                        NULL, &vp, 1) != TABLE_ERROR_NONE) {
        ssl_mutex_off(s);
        return FALSE;
    }
    memcpy(vp, &expiry, sizeof(time_t));
    memcpy((char *)vp+sizeof(time_t), ucaData, nData);
    ssl_mutex_off(s);

    /* allow the regular expiring to occur */
    ssl_scache_shmht_expire(s);

    return TRUE;
}