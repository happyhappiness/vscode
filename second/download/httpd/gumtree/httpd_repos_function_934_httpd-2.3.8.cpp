BOOL ssl_scache_store(server_rec *s, UCHAR *id, int idlen,
                      apr_time_t expiry, SSL_SESSION *sess,
                      apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    unsigned char encoded[SSL_SESSION_MAX_DER], *ptr;
    unsigned int len;
    apr_status_t rv;

    /* Serialise the session. */
    len = i2d_SSL_SESSION(sess, NULL);
    if (len > sizeof encoded) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "session is too big (%u bytes)", len);
        return FALSE;
    }

    ptr = encoded;
    len = i2d_SSL_SESSION(sess, &ptr);

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_on(s);
    }
    
    rv = mc->sesscache->store(mc->sesscache_context, s, id, idlen, 
                              expiry, encoded, len, p);

    if (mc->sesscache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        ssl_mutex_off(s);
    }

    return rv == APR_SUCCESS ? TRUE : FALSE;
}