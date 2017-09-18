
    for (i=0; version_components[i]; i++) {
        vals[i] = ssl_add_version_component(p, s,
                                            version_components[i]);
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
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
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Initializing %s library", SSL_LIBRARY_NAME);

    CRYPTO_malloc_init();
    SSL_load_error_strings();
    SSL_library_init();
}

