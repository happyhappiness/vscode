void simple_single_process_hack(simple_core_t * sc)
{
    apr_status_t rv;
    /* Normally this is only ran in the child processes, but we want to do it here too... */
    rv = simple_setup_listeners(sc);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_single_child_hack: simple_setup_listeners failed");
    }
}