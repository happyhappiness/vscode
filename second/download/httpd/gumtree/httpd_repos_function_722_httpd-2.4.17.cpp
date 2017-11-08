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

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01951)
                 "stapling_cb: OCSP Stapling callback called");

    cinf = stapling_get_certinfo(s, mctx, ssl);
    if (cinf == NULL) {
        return SSL_TLSEXT_ERR_NOACK;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01952)
                 "stapling_cb: retrieved cached certificate data");

    rv = get_and_check_cached_response(s, mctx, &rsp, cinf, conn->pool);
    if (rv != 0) {
        return rv;
    }

    if (rsp == NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01954)
                     "stapling_cb: renewing cached response");
        stapling_refresh_mutex_on(s);
        /* Maybe another request refreshed the OCSP response while this
         * thread waited for the mutex.  Check again.
         */
        rv = get_and_check_cached_response(s, mctx, &rsp, cinf, conn->pool);
        if (rv != 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_cb: error checking for cached response "
                         "after obtaining refresh mutex");
            stapling_refresh_mutex_off(s);
            return rv;
        }
        else if (rsp) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_cb: don't need to refresh cached response "
                         "after obtaining refresh mutex");
            stapling_refresh_mutex_off(s);
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "stapling_cb: still must refresh cached response "
                         "after obtaining refresh mutex");
            rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, conn->pool);
            stapling_refresh_mutex_off(s);

            if (rv == TRUE) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                             "stapling_cb: success renewing response");
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01955)
                             "stapling_cb: fatal error renewing response");
                return SSL_TLSEXT_ERR_ALERT_FATAL;
            }
        }
    }

    if (rsp) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01956)
                     "stapling_cb: setting response");
        if (!stapling_set_response(ssl, rsp))
            return SSL_TLSEXT_ERR_ALERT_FATAL;
        return SSL_TLSEXT_ERR_OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01957)
                 "stapling_cb: no response available");

    return SSL_TLSEXT_ERR_NOACK;

}