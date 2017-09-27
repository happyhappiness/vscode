**  _________________________________________________________________
*/

void ssl_scache_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    /*
     * Warn the user that he should use the session cache.
     * But we can operate without it, of course.
     */
    if (mc->nSessionCacheMode == SSL_SCMODE_UNSET) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "Init: Session Cache is not configured "
                     "[hint: SSLSessionCache]");
        mc->nSessionCacheMode = SSL_SCMODE_NONE;
        return;
    }

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_init(s, p);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_init(s, p);
#endif
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB) {
        void *data;
        const char *userdata_key = "ssl_scache_init";

        apr_pool_userdata_get(&data, userdata_key, s->process->pool);
        if (!data) {
            apr_pool_userdata_set((const void *)1, userdata_key,
                                  apr_pool_cleanup_null, s->process->pool);
            return;
        }
        ssl_scache_shmcb_init(s, p);
    }
}

void ssl_scache_kill(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_kill(s);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        ssl_scache_shmcb_kill(s);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_kill(s);
#endif
    return;
}

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

SSL_SESSION *ssl_scache_retrieve(server_rec *s, UCHAR *id, int idlen)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSL_SESSION *sess = NULL;

    if (mc->nSessionCacheMode == SSL_SCMODE_DBM)
        sess = ssl_scache_dbm_retrieve(s, id, idlen);
    else if (mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        sess = ssl_scache_shmcb_retrieve(s, id, idlen);
#ifdef HAVE_DISTCACHE
    else if (mc->nSessionCacheMode == SSL_SCMODE_DC)
        sess = ssl_scache_dc_retrieve(s, id, idlen);
#endif
    return sess;
}

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

/*  _________________________________________________________________
**
**  SSL Extension to mod_status
**  _________________________________________________________________
*/
static int ssl_ext_status_hook(request_rec *r, int flags)
{
    SSLSrvConfigRec *sc = mySrvConfig(r->server);

    if (sc == NULL || flags & AP_STATUS_SHORT)
        return OK;

    ap_rputs("<hr>\n", r);
    ap_rputs("<table cellspacing=0 cellpadding=0>\n", r);
    ap_rputs("<tr><td bgcolor=\"#000000\">\n", r);
    ap_rputs("<b><font color=\"#ffffff\" face=\"Arial,Helvetica\">SSL/TLS Session Cache Status:</font></b>\r", r);
    ap_rputs("</td></tr>\n", r);
    ap_rputs("<tr><td bgcolor=\"#ffffff\">\n", r);

    if (sc->mc->nSessionCacheMode == SSL_SCMODE_DBM)
        ssl_scache_dbm_status(r, flags, r->pool);
    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_SHMCB)
        ssl_scache_shmcb_status(r, flags, r->pool);
#ifdef HAVE_DISTCACHE
    else if (sc->mc->nSessionCacheMode == SSL_SCMODE_DC)
        ssl_scache_dc_status(r, flags, r->pool);
#endif

    ap_rputs("</td></tr>\n", r);
    ap_rputs("</table>\n", r);
    return OK;
}

