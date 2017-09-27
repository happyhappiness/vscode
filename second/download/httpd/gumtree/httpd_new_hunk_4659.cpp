    else {
        one_process = ap_exists_config_define("ONE_PROCESS");
        no_detach = ap_exists_config_define("NO_DETACH");
        foreground = ap_exists_config_define("FOREGROUND");
    }

    retained = ap_retained_data_get(userdata_key);
    if (!retained) {
        retained = ap_retained_data_create(userdata_key, sizeof(*retained));
        retained->mpm = ap_unixd_mpm_get_retained_data();
        retained->max_daemons_limit = -1;
        if (retained->mpm->module_loads) {
            test_atomics = 1;
        }
    }
    retained->mpm->mpm_state = AP_MPMQ_STARTING;
    if (retained->mpm->baton != retained) {
        retained->mpm->was_graceful = 0;
        retained->mpm->baton = retained;
    }
    ++retained->mpm->module_loads;

    /* test once for correct operation of fdqueue */
    if (test_atomics || retained->mpm->module_loads == 2) {
        static apr_uint32_t foo1, foo2;

        apr_atomic_set32(&foo1, 100);
        foo2 = apr_atomic_add32(&foo1, -10);
        if (foo2 != 100 || foo1 != 90) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL, APLOGNO(02405)
                         "atomics not working as expected - add32 of negative number");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    /* sigh, want this only the second time around */
    if (retained->mpm->module_loads == 2) {
        rv = apr_pollset_create(&event_pollset, 1, plog,
                                APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00495)
                         "Couldn't create a Thread Safe Pollset. "
                         "Is it supported on your platform?"
