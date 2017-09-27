     * they should change to a user with write access to logs/ alone.
     */
    ap_sys_privileges_handlers(1);

    if (!strcasecmp(signal_arg, "runservice")
            && (service_to_start_success != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL, APLOGNO(00438)
                     "%s: Unable to start the service manager.",
                     service_name);
        exit(APEXIT_INIT);
    }
    else if (!one_process && !my_generation) {
        /* Open a null handle to soak stdout in this process.
