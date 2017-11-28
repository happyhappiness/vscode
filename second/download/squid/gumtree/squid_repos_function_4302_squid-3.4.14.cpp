static void
ssl_initialize(void)
{
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();

#if HAVE_OPENSSL_ENGINE_H
    if (Config.SSL.ssl_engine) {
        ENGINE *e;
        if (!(e = ENGINE_by_id(Config.SSL.ssl_engine)))
            fatalf("Unable to find SSL engine '%s'\n", Config.SSL.ssl_engine);

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            int ssl_error = ERR_get_error();
            fatalf("Failed to initialise SSL engine: %s\n", ERR_error_string(ssl_error, NULL));
        }
    }
#else
    if (Config.SSL.ssl_engine)
        fatalf("Your OpenSSL has no SSL engine support\n");
#endif

    ssl_ex_index_server = SSL_get_ex_new_index(0, (void *) "server", NULL, NULL, NULL);
    ssl_ctx_ex_index_dont_verify_domain = SSL_CTX_get_ex_new_index(0, (void *) "dont_verify_domain", NULL, NULL, NULL);
    ssl_ex_index_cert_error_check = SSL_get_ex_new_index(0, (void *) "cert_error_check", NULL, &ssl_dupAclChecklist, &ssl_freeAclChecklist);
    ssl_ex_index_ssl_error_detail = SSL_get_ex_new_index(0, (void *) "ssl_error_detail", NULL, NULL, &ssl_free_ErrorDetail);
    ssl_ex_index_ssl_peeked_cert  = SSL_get_ex_new_index(0, (void *) "ssl_peeked_cert", NULL, NULL, &ssl_free_X509);
    ssl_ex_index_ssl_errors =  SSL_get_ex_new_index(0, (void *) "ssl_errors", NULL, NULL, &ssl_free_SslErrors);
    ssl_ex_index_ssl_cert_chain = SSL_get_ex_new_index(0, (void *) "ssl_cert_chain", NULL, NULL, &ssl_free_CertChain);
    ssl_ex_index_ssl_validation_counter = SSL_get_ex_new_index(0, (void *) "ssl_validation_counter", NULL, NULL, &ssl_free_int);
}