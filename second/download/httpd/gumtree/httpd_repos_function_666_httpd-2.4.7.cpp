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