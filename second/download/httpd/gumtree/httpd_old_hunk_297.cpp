     * should take place. This cannot work.
     */
    if (mctx->auth.verify_mode == SSL_CVERIFY_REQUIRE) {
        ca_list = (STACK_OF(X509_NAME) *)SSL_CTX_get_client_CA_list(ctx);

        if (sk_X509_NAME_num(ca_list) == 0) {
            ssl_log(s, SSL_LOG_WARN,
                    "Init: Oops, you want to request client authentication, "
                    "but no CAs are known for verification!? "
                    "[Hint: SSLCACertificate*]");
        }
    }
}

static void ssl_init_ctx_cipher_suite(server_rec *s,
                                      apr_pool_t *p,
