int simple_child_loop(simple_core_t * sc)
{
    apr_status_t rv;

    rv = simple_setup_pollcb(sc);
    if (rv) {
        return rv;
    }

    /* XXXXX: Hack. Reseting parts of the simple core needs to be more
     * thought out than this. 
     */
    APR_RING_INIT(&sc->timer_ring, simple_timer_t, link);

    rv = simple_setup_workers(sc);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_child_loop: simple_setup_workers failed");
        return !OK;
    }

    rv = simple_setup_listeners(sc);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_child_loop: simple_setup_sockets failed");
        return !OK;
    }

    rv = simple_setup_privs(sc);
    if (rv) {
        /* simple_setup_privs already logged error */
        return !OK;
    }

    ap_run_child_init(sc->pool, ap_server_conf);

    return simple_run_loop(sc);
}