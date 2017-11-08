static int
simple_pre_config(apr_pool_t * pconf, apr_pool_t * plog, apr_pool_t * ptemp)
{
    int run_debug;
    apr_status_t rv;
    simple_core_t *sc;

    /* this is our first 'real' entry point, so setup everything here. */
    rv = simple_core_init_once();

    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_core_init_once: Fatal Error Encountered");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    sc = simple_core_get();

    sc->restart_num++;

    run_debug = ap_exists_config_define("DEBUG");

    if (run_debug) {
        sc->run_foreground = 1;
        sc->run_single_process = 1;
    }
    else {
        sc->run_foreground = ap_exists_config_define("FOREGROUND");
    }

    if (sc->restart_num == 2) {

        if (sc->run_foreground) {
            rv = apr_proc_detach(APR_PROC_DETACH_FOREGROUND);
        }
        else {
            rv = apr_proc_detach(APR_PROC_DETACH_DAEMONIZE);
        }

        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                         "simple_pre_config: apr_proc_detach(%s) failed",
                         sc->run_foreground ? "FOREGROUND" : "DAEMONIZE");
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }

    return OK;
}