        retained = ap_retained_data_create(userdata_key, sizeof(*retained));
        retained->max_daemons_limit = -1;
        retained->idle_spawn_rate = 1;
    }
    ++retained->module_loads;
    if (retained->module_loads == 2) {
        rv = apr_pollset_create(&event_pollset, 1, plog,
                                APR_POLLSET_THREADSAFE | APR_POLLSET_NOCOPY);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL, APLOGNO(00495)
                         "Couldn't create a Thread Safe Pollset. "
                         "Is it supported on your platform?"
