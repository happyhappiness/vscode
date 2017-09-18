     *  Initialise list of loaded modules
     */
    ap_loaded_modules = (module **)apr_palloc(process->pool,
        sizeof(module *) * (total_modules + DYNAMIC_MODULE_LIMIT + 1));

    if (ap_loaded_modules == NULL) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Ouch!  Out of memory in ap_setup_prelinked_modules()!");
    }

    for (m = ap_preloaded_modules, m2 = ap_loaded_modules; *m != NULL; )
        *m2++ = *m++;

