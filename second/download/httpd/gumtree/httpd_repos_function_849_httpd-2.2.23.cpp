BOOL ssl_scache_dc_store(server_rec *s, UCHAR *id, int idlen,
                           time_t timeout, SSL_SESSION * pSession)
{
    unsigned char der[SSL_SESSION_MAX_DER];
    int der_len;
    unsigned char *pder = der;
    SSLModConfigRec *mc = myModConfig(s);
    DC_CTX *ctx = mc->tSessionCacheDataTable;

    /* Serialise the SSL_SESSION object */
    if ((der_len = i2d_SSL_SESSION(pSession, NULL)) > SSL_SESSION_MAX_DER)
        return FALSE;
    i2d_SSL_SESSION(pSession, &pder);
    /* !@#$%^ - why do we deal with *absolute* time anyway??? */
    timeout -= time(NULL);
    /* Send the serialised session to the distributed cache context */
    if (!DC_CTX_add_session(ctx, id, idlen, der, der_len,
                            (unsigned long)timeout * 1000)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'add_session' failed");
        return FALSE;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'add_session' successful");
    return TRUE;
}