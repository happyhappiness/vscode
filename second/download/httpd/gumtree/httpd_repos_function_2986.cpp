static int simple_setup_privs(simple_core_t * sc)
{
    int rv = ap_run_drop_privileges(sc->pool, ap_server_conf);

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_setup_privs: ap_run_drop_privileges failed");
        return rv;
    }

    return 0;
}