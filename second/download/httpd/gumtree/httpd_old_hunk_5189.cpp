#endif

    /*
     * SSL external crypto device ("engine") support
     */
#if defined(HAVE_OPENSSL_ENGINE_H) && defined(HAVE_ENGINE_INIT)
    ssl_init_Engine(base_server, p);
#endif

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01883)
                 "Init: Initialized %s library", SSL_LIBRARY_NAME);

    /*
