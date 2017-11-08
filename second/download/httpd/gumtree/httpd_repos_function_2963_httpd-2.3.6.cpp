int simple_main_loop(simple_core_t * sc)
{
    apr_status_t rv;

    rv = simple_setup_pollcb(sc);
    if (rv) {
        return rv;
    }
    
    rv = simple_setup_workers(sc);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_main_loop: simple_setup_workers failed");
        return !OK;
    }

    rv = simple_main_setup_timers(sc);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_main_loop: simple_setup_timers failed");
        return !OK;
    }

    return simple_run_loop(sc);
}