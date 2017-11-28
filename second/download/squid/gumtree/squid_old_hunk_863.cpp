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
