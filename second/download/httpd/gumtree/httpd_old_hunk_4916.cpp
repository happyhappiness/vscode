            && (service_to_start_success != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL, APLOGNO(00438)
                     "%s: Unable to start the service manager.",
                     service_name);
        exit(APEXIT_INIT);
    }
    else if (!one_process && !my_generation) {
        /* Open a null handle to soak stdout in this process.
         * We need to emulate apr_proc_detach, unix performs this
         * same check in the pre_config hook (although it is
         * arguably premature).  Services already fixed this.
         */
        apr_file_t *nullfile;
