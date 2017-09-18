    {
        /* The child process or in one_process (debug) mode 
         */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is running", my_pid);

        child_main();

        ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                     "Child %d: Child process is exiting", my_pid);        
        return 1;
    }
    else 
