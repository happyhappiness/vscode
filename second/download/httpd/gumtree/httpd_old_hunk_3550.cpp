    if (!(ssl_ctx = SSL_CTX_new(meth))) {
        BIO_printf(bio_err, "Could not initialize SSL Context.\n");
        ERR_print_errors(bio_err);
        exit(1);
    }
    SSL_CTX_set_options(ssl_ctx, SSL_OP_ALL);
    if (ssl_cipher != NULL) {
        if (!SSL_CTX_set_cipher_list(ssl_ctx, ssl_cipher)) {
            fprintf(stderr, "error setting cipher list [%s]\n", ssl_cipher);
        ERR_print_errors_fp(stderr);
        exit(1);
    }
