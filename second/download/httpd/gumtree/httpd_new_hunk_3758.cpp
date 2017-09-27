err:
    rv = FALSE;
    goto done;
}

/*
 * SSL stapling mutex operations. Similar to SSL mutex except mutexes are
 * mandatory if stapling is enabled.
 */
static int ssl_stapling_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    apr_status_t rv;

    /* already init or stapling not enabled? */
    if (mc->stapling_refresh_mutex || sc->server->stapling_enabled != TRUE) {
        return TRUE;
    }

    /* need a cache mutex? */
    if (mc->stapling_cache->flags & AP_SOCACHE_FLAG_NOTMPSAFE) {
        if ((rv = ap_global_mutex_create(&mc->stapling_cache_mutex, NULL,
                                         SSL_STAPLING_CACHE_MUTEX_TYPE, NULL, s,
                                         s->process->pool, 0)) != APR_SUCCESS) {
            return FALSE;
        }
    }

    /* always need stapling_refresh_mutex */
    if ((rv = ap_global_mutex_create(&mc->stapling_refresh_mutex, NULL,
                                     SSL_STAPLING_REFRESH_MUTEX_TYPE, NULL, s,
                                     s->process->pool, 0)) != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}

static int stapling_mutex_reinit_helper(server_rec *s, apr_pool_t *p, 
                                        apr_global_mutex_t **mutex,
                                        const char *type)
{
    apr_status_t rv;
    const char *lockfile;

    lockfile = apr_global_mutex_lockfile(*mutex);
    if ((rv = apr_global_mutex_child_init(mutex,
                                          lockfile, p)) != APR_SUCCESS) {
        if (lockfile) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01946)
                         "Cannot reinit %s mutex with file `%s'",
                         type, lockfile);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01947)
                         "Cannot reinit %s mutex", type);
        }
        return FALSE;
    }
    return TRUE;
}

int ssl_stapling_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (mc->stapling_cache_mutex != NULL
        && stapling_mutex_reinit_helper(s, p, &mc->stapling_cache_mutex,
                                        SSL_STAPLING_CACHE_MUTEX_TYPE) == FALSE) {
        return FALSE;
    }

    if (mc->stapling_refresh_mutex != NULL
        && stapling_mutex_reinit_helper(s, p, &mc->stapling_refresh_mutex,
                                        SSL_STAPLING_REFRESH_MUTEX_TYPE) == FALSE) {
        return FALSE;
    }

    return TRUE;
}

static int stapling_mutex_on(server_rec *s, apr_global_mutex_t *mutex,
                             const char *name)
{
    apr_status_t rv;

    if ((rv = apr_global_mutex_lock(mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01948)
                     "Failed to acquire OCSP %s lock", name);
        return FALSE;
    }
    return TRUE;
}

static int stapling_mutex_off(server_rec *s, apr_global_mutex_t *mutex,
                              const char *name)
{
    apr_status_t rv;

    if ((rv = apr_global_mutex_unlock(mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01949)
                     "Failed to release OCSP %s lock", name);
        return FALSE;
    }
    return TRUE;
}

static int stapling_cache_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_on(s, mc->stapling_cache_mutex,
                             SSL_STAPLING_CACHE_MUTEX_TYPE);
}

static int stapling_cache_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_off(s, mc->stapling_cache_mutex,
                              SSL_STAPLING_CACHE_MUTEX_TYPE);
}

static int stapling_refresh_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_on(s, mc->stapling_refresh_mutex,
                             SSL_STAPLING_REFRESH_MUTEX_TYPE);
}

static int stapling_refresh_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    return stapling_mutex_off(s, mc->stapling_refresh_mutex,
                              SSL_STAPLING_REFRESH_MUTEX_TYPE);
}

static int get_and_check_cached_response(server_rec *s, modssl_ctx_t *mctx,
                                         OCSP_RESPONSE **rsp, certinfo *cinf, 
                                         apr_pool_t *p)
{
    BOOL ok;
    int rv;

    AP_DEBUG_ASSERT(*rsp == NULL);

    /* Check to see if we already have a response for this certificate */
    stapling_get_cached_response(s, rsp, &ok, cinf, p);

    if (*rsp) {
        /* see if response is acceptable */
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01953)
                     "stapling_cb: retrieved cached response");
        rv = stapling_check_response(s, mctx, cinf, *rsp, NULL);
        if (rv == SSL_TLSEXT_ERR_ALERT_FATAL) {
            OCSP_RESPONSE_free(*rsp);
            *rsp = NULL;
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        }
        else if (rv == SSL_TLSEXT_ERR_NOACK) {
            /* Error in response. If this error was not present when it was
             * stored (i.e. response no longer valid) then it can be
             * renewed straight away.
             *
             * If the error *was* present at the time it was stored then we
             * don't renew the response straight away; we just wait for the
             * cached response to expire.
             */
            if (ok) {
                OCSP_RESPONSE_free(*rsp);
                *rsp = NULL;
            }
            else if (!mctx->stapling_return_errors) {
                OCSP_RESPONSE_free(*rsp);
                *rsp = NULL;
                return SSL_TLSEXT_ERR_NOACK;
            }
        }
    }
    return 0;
}

/* Certificate Status callback. This is called when a client includes a
 * certificate status request extension.
 *
 * Check for cached responses in session cache. If valid send back to
 * client.  If absent or no longer valid, query responder and update
 * cache.
 */
static int stapling_cb(SSL *ssl, void *arg)
{
    conn_rec *conn      = (conn_rec *)SSL_get_app_data(ssl);
    server_rec *s       = mySrvFromConn(conn);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    SSLConnRec *sslconn = myConnConfig(conn);
    modssl_ctx_t *mctx  = myCtxConfig(sslconn, sc);
    certinfo *cinf = NULL;
    OCSP_RESPONSE *rsp = NULL;
    int rv;

    if (sc->server->stapling_enabled != TRUE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01950)
                     "stapling_cb: OCSP Stapling disabled");
        return SSL_TLSEXT_ERR_NOACK;
    }
