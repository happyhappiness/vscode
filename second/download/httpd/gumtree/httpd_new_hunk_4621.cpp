
    if (SSLeay() < MODSSL_LIBRARY_VERSION) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server, APLOGNO(01882)
                     "Init: this version of mod_ssl was compiled against "
                     "a newer library (%s, version currently loaded is %s)"
                     " - may result in undefined or erroneous behavior",
                     MODSSL_LIBRARY_TEXT, MODSSL_LIBRARY_DYNTEXT);
    }

    /* We initialize mc->pid per-process in the child init,
     * but it should be initialized for startup before we
     * call ssl_rand_seed() below.
     */
