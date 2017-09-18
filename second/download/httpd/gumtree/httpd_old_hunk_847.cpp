    }
    if (sconf->max_cache_object_size >= sconf->max_cache_size) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
                     "MCacheSize must be greater than MCacheMaxObjectSize");
        return DONE;
    }
    ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded_mpm);
    if (threaded_mpm) {
        apr_thread_mutex_create(&sconf->lock, APR_THREAD_MUTEX_DEFAULT, p);
    }

    sconf->cache_cache = cache_init(sconf->max_object_cnt,
