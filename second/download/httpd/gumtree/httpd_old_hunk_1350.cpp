
    if ((parent_pid != my_pid) || one_process)
    {
        /* The child process or in one_process (debug) mode
         */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is running", my_pid);

        child_main(pconf);

        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is exiting", my_pid);
        return 1;
    }
    else
    {
        /* A real-honest to goodness parent */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
