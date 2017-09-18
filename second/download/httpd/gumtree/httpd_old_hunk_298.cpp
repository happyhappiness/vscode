     *  Configure SSL Cipher Suite
     */
    if (!suite) {
        return;
    }

    ssl_log(s, SSL_LOG_TRACE|SSL_INIT,
            "Configuring permitted SSL ciphers [%s]", 
            suite);

    if (!SSL_CTX_set_cipher_list(ctx, suite)) {
        ssl_log(s, SSL_LOG_ERROR|SSL_ADD_SSLERR|SSL_INIT,
                "Unable to configure permitted SSL ciphers");
        ssl_die();
    }
}

static void ssl_init_ctx_crl(server_rec *s,
                             apr_pool_t *p,
