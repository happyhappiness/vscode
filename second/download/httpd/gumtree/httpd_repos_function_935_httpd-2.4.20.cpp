static int ssl_hook_pre_config(apr_pool_t *pconf,
                               apr_pool_t *plog,
                               apr_pool_t *ptemp)
{
    /* We must register the library in full, to ensure our configuration
     * code can successfully test the SSL environment.
     */
    CRYPTO_malloc_init();
    ERR_load_crypto_strings();
    SSL_load_error_strings();
    SSL_library_init();
#if HAVE_ENGINE_LOAD_BUILTIN_ENGINES
    ENGINE_load_builtin_engines();
#endif
    OpenSSL_add_all_algorithms();
    OPENSSL_load_builtin_modules();

    if (OBJ_txt2nid("id-on-dnsSRV") == NID_undef) {
        (void)OBJ_create("1.3.6.1.5.5.7.8.7", "id-on-dnsSRV",
                         "SRVName otherName form");
    }

    /*
     * Let us cleanup the ssl library when the module is unloaded
     */
    apr_pool_cleanup_register(pconf, NULL, ssl_cleanup_pre_config,
                                           apr_pool_cleanup_null);

    /* Register us to handle mod_log_config %c/%x variables */
    ssl_var_log_config_register(pconf);

    /* Register to handle mod_status status page generation */
    ssl_scache_status_register(pconf);

    /* Register mutex type names so they can be configured with Mutex */
    ap_mutex_register(pconf, SSL_CACHE_MUTEX_TYPE, NULL, APR_LOCK_DEFAULT, 0);
#ifdef HAVE_OCSP_STAPLING
    ap_mutex_register(pconf, SSL_STAPLING_CACHE_MUTEX_TYPE, NULL,
                      APR_LOCK_DEFAULT, 0);
    ap_mutex_register(pconf, SSL_STAPLING_REFRESH_MUTEX_TYPE, NULL,
                      APR_LOCK_DEFAULT, 0);
#endif

    return OK;
}