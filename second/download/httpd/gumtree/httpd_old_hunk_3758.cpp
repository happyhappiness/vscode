err:
    rv = FALSE;
    goto done;
}

/*
 * SSLStaplingMutex operations. Similar to SSL mutex except a mutex is
 * mandatory if stapling is enabled.
 */
static int ssl_stapling_mutex_init(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    SSLSrvConfigRec *sc = mySrvConfig(s);
    apr_status_t rv;

    if (mc->stapling_mutex || sc->server->stapling_enabled != TRUE) {
        return TRUE;
    }

    if ((rv = ap_global_mutex_create(&mc->stapling_mutex, NULL,
                                     SSL_STAPLING_MUTEX_TYPE, NULL, s,
                                     s->process->pool, 0)) != APR_SUCCESS) {
        return FALSE;
    }

    return TRUE;
}

int ssl_stapling_mutex_reinit(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;
    const char *lockfile;

    if (mc->stapling_mutex == NULL) {
        return TRUE;
    }

    lockfile = apr_global_mutex_lockfile(mc->stapling_mutex);
    if ((rv = apr_global_mutex_child_init(&mc->stapling_mutex,
                                          lockfile, p)) != APR_SUCCESS) {
        if (lockfile) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(01946)
                         "Cannot reinit %s mutex with file `%s'",
                         SSL_STAPLING_MUTEX_TYPE, lockfile);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01947)
                         "Cannot reinit %s mutex", SSL_STAPLING_MUTEX_TYPE);
        }
        return FALSE;
    }
    return TRUE;
}

static int stapling_mutex_on(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_lock(mc->stapling_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01948)
                     "Failed to acquire OCSP stapling lock");
        return FALSE;
    }
    return TRUE;
}

static int stapling_mutex_off(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);
    apr_status_t rv;

    if ((rv = apr_global_mutex_unlock(mc->stapling_mutex)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s, APLOGNO(01949)
                     "Failed to release OCSP stapling lock");
        return FALSE;
    }
    return TRUE;
}

/* Certificate Status callback. This is called when a client includes a
 * certificate status request extension.
 *
 * Check for cached responses in session cache. If valid send back to
 * client.  If absent or no longer valid query responder and update
 * cache. */
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
    BOOL ok;

    if (sc->server->stapling_enabled != TRUE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01950)
                     "stapling_cb: OCSP Stapling disabled");
        return SSL_TLSEXT_ERR_NOACK;
    }
