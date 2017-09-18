
    for (i=0; version_components[i]; i++) {
        vals[i] = ssl_add_version_component(p, s,
                                            version_components[i]);
    }

    ssl_log(s, SSL_LOG_INFO,
            "Server: %s, Interface: %s, Library: %s",
            AP_SERVER_BASEVERSION,
            vals[1],  /* SSL_VERSION_INTERFACE */
            vals[2]); /* SSL_VERSION_LIBRARY */
}


/*
 *  Initialize SSL library
 */
static void ssl_init_SSLLibrary(server_rec *s)
{
    ssl_log(s, SSL_LOG_INFO,
            "Init: Initializing %s library", SSL_LIBRARY_NAME);

    CRYPTO_malloc_init();
    SSL_load_error_strings();
    SSL_library_init();
}

