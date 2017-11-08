SSL_SESSION *ssl_scache_dc_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    unsigned char der[SSL_SESSION_MAX_DER];
    unsigned int der_len;
    SSL_SESSION *pSession;
    MODSSL_D2I_SSL_SESSION_CONST unsigned char *pder = der;
    SSLModConfigRec *mc = myModConfig(s);
    DC_CTX *ctx = mc->tSessionCacheDataTable;

    /* Retrieve any corresponding session from the distributed cache context */
    if (!DC_CTX_get_session(ctx, id, idlen, der, SSL_SESSION_MAX_DER,
                            &der_len)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'get_session' MISS");
        return NULL;
    }
    if (der_len > SSL_SESSION_MAX_DER) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'get_session' OVERFLOW");
        return NULL;
    }
    pSession = d2i_SSL_SESSION(NULL, &pder, der_len);
    if (!pSession) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'get_session' CORRUPT");
        return NULL;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'get_session' HIT");
    return pSession;
}