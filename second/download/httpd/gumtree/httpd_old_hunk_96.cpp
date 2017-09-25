 */
static void ssl_init_SSLLibrary(server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Initializing %s library", SSL_LIBRARY_NAME);

    CRYPTO_malloc_init();
    SSL_load_error_strings();
    SSL_library_init();
}

/*
 * Handle the Temporary RSA Keys and DH Params
