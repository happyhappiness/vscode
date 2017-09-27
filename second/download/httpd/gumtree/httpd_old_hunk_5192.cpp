
/*
 * Support for external a Crypto Device ("engine"), usually
 * a hardware accellerator card for crypto operations.
 */
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
void ssl_init_Engine(server_rec *s, apr_pool_t *p)
{
    SSLModConfigRec *mc = myModConfig(s);
    ENGINE *e;

    if (mc->szCryptoDevice) {
        if (!(e = ENGINE_by_id(mc->szCryptoDevice))) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01888)
                         "Init: Failed to load Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            ssl_die(s);
        }

        if (strEQ(mc->szCryptoDevice, "chil")) {
            ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
        }

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01889)
                         "Init: Failed to enable Crypto Device API `%s'",
                         mc->szCryptoDevice);
            ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
            ssl_die(s);
        }
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01890)
                     "Init: loaded Crypto Device API `%s'",
                     mc->szCryptoDevice);

        ENGINE_free(e);
    }
}
#endif

static void ssl_init_server_check(server_rec *s,
                                  apr_pool_t *p,
                                  apr_pool_t *ptemp,
                                  modssl_ctx_t *mctx)
{
    /*
     * check for important parameters and the
     * possibility that the user forgot to set them.
     */
    if (!mctx->pks->cert_files[0] && !mctx->pkcs7) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01891)
                "No SSL Certificate set [hint: SSLCertificateFile]");
        ssl_die(s);
    }

    /*
     *  Check for problematic re-initializations
     */
    if (mctx->pks->certs[SSL_AIDX_RSA] ||
        mctx->pks->certs[SSL_AIDX_DSA]
#ifdef HAVE_ECC
      || mctx->pks->certs[SSL_AIDX_ECC]
#endif
        )
    {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01892)
                "Illegal attempt to re-initialise SSL for server "
                "(SSLEngine On should go in the VirtualHost, not in global scope.)");
        ssl_die(s);
    }
}

#ifdef HAVE_TLSEXT
static void ssl_init_ctx_tls_extensions(server_rec *s,
                                        apr_pool_t *p,
                                        apr_pool_t *ptemp,
                                        modssl_ctx_t *mctx)
{
    /*
     * Configure TLS extensions support
     */
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01893)
                 "Configuring TLS extension handling");

