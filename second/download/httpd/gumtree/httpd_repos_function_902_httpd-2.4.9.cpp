static apr_status_t ssl_cleanup_pre_config(void *data)
{
    /*
     * Try to kill the internals of the SSL library.
     */
    /* Corresponds to OPENSSL_load_builtin_modules():
     * XXX: borrowed from apps.h, but why not CONF_modules_free()
     * which also invokes CONF_modules_finish()?
     */
    CONF_modules_unload(1);
    /* Corresponds to SSL_library_init: */
    EVP_cleanup();
#if HAVE_ENGINE_LOAD_BUILTIN_ENGINES
    ENGINE_cleanup();
#endif
    ERR_remove_state(0);

    /* Don't call ERR_free_strings here; ERR_load_*_strings only
     * actually load the error strings once per process due to static
     * variable abuse in OpenSSL. */

    /* Also don't call CRYPTO_cleanup_all_ex_data here; any registered
     * ex_data indices may have been cached in static variables in
     * OpenSSL; removing them may cause havoc.  Notably, with OpenSSL
     * versions >= 0.9.8f, COMP_CTX cleanups would not be run, which
     * could result in a per-connection memory leak (!). */

    /*
     * TODO: determine somewhere we can safely shove out diagnostics
     *       (when enabled) at this late stage in the game:
     * CRYPTO_mem_leaks_fp(stderr);
     */
    return APR_SUCCESS;
}