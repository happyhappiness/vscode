         * and later, there's SSL_CTX_set_current_cert, which allows
         * iterating over all certs in an SSL_CTX (including those possibly
         * loaded via SSLOpenSSLConfCmd Certificate), so for 1.0.2 and
         * later, we defer to the code in ssl_init_server_ctx.
         */
        if ((mctx->stapling_enabled == TRUE) &&
            !ssl_stapling_init_cert(s, mctx, cert)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02567)
                         "Unable to configure certificate %s for stapling",
                         key_id);
        }
#endif

