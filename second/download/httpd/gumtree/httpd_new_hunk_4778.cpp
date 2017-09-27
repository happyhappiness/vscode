                 suite);

    if (!SSL_CTX_set_cipher_list(ctx, suite)) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01898)
                "Unable to configure permitted SSL ciphers");
        ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
        ssl_die(s);
    }
}

static void ssl_init_ctx_crl(server_rec *s,
                             apr_pool_t *p,
                             apr_pool_t *ptemp,
