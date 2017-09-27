
/*
 * Support for external a Crypto Device ("engine"), usually
 * a hardware accellerator card for crypto operations.
 */
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
apr_status_t ssl_init_Engine(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    ENGINE *e;

    if (mc->szCryptoDevice) {
        if (!(e = ENGINE_by_id(mc->szCryptoDevice))) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01888)
                         "Init: Failed to load Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        }

        if (strEQ(mc->szCryptoDevice, "chil")) {
            ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
        }

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01889)
                         "Init: Failed to enable Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            return ssl_die(s);
        }
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01890)
                     "Init: loaded Crypto Device API `%s'",
                     mc->szCryptoDevice);

        ENGINE_free(e);
    }

    return APR_SUCCESS;
}
#endif

#ifdef HAVE_TLSEXT
static apr_status_t ssl_init_ctx_tls_extensions(server_rec *s,
                                                apr_pool_t *p,
                                                apr_pool_t *ptemp,
                                                modssl_ctx_t *mctx)
{
    apr_status_t rv;

    /*
     * Configure TLS extensions support
     */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01893)
                 "Configuring TLS extension handling");

