
    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();

#if HAVE_OPENSSL_ENGINE_H
    if (::Config.SSL.ssl_engine) {
        ENGINE *e;
        if (!(e = ENGINE_by_id(::Config.SSL.ssl_engine)))
            fatalf("Unable to find SSL engine '%s'\n", ::Config.SSL.ssl_engine);

        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            const int ssl_error = ERR_get_error();
