static apr_status_t ssl_cleanup_pre_config(void *data)
{
    /*
     * Try to kill the internals of the SSL library.
     */
#ifdef HAVE_FIPS
    FIPS_mode_set(0);
#endif
    /* Corresponds to OBJ_create()s */
    OBJ_cleanup();
    /* Corresponds to OPENSSL_load_builtin_modules() */
    CONF_modules_free();
    /* Corresponds to SSL_library_init: */
    EVP_cleanup();
#if HAVE_ENGINE_LOAD_BUILTIN_ENGINES
    ENGINE_cleanup();
#endif
#if OPENSSL_VERSION_NUMBER >= 0x1000200fL
    SSL_COMP_free_compression_methods();
#endif

    /* Usually needed per thread, but this parent process is single-threaded */
#if OPENSSL_VERSION_NUMBER < 0x10100000L
#if OPENSSL_VERSION_NUMBER >= 0x1000000fL
    ERR_remove_thread_state(NULL);
#else
    ERR_remove_state(0);
#endif
#endif

    /* Don't call ERR_free_strings in earlier versions, ERR_load_*_strings only
     * actually loaded the error strings once per process due to static
     * variable abuse in OpenSSL. */
#if (OPENSSL_VERSION_NUMBER >= 0x00090805f)
    ERR_free_strings();
#endif

    /* Also don't call CRYPTO_cleanup_all_ex_data when linked statically here;
     * any registered ex_data indices may have been cached in static variables
     * in OpenSSL; removing them may cause havoc.  Notably, with OpenSSL
     * versions >= 0.9.8f, COMP_CTX cleanups would not be run, which
     * could result in a per-connection memory leak (!). */
    if (!modssl_running_statically) {
        CRYPTO_cleanup_all_ex_data();
    }

    /*
     * TODO: determine somewhere we can safely shove out diagnostics
     *       (when enabled) at this late stage in the game:
     * CRYPTO_mem_leaks_fp(stderr);
     */
    return APR_SUCCESS;
}