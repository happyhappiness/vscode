{
    apr_status_t rv;
    pid_t otherpid;
    int running = 0;
    int have_pid_file = 0;
    const char *status;
    
    *exit_status = 0;

    rv = ap_read_pid(pconf, ap_pid_fname, &otherpid);
    if (rv != APR_SUCCESS) {
        if (rv != APR_ENOENT) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rv, NULL,
                         "Error retrieving pid file %s", ap_pid_fname);
            *exit_status = 1;
            return 1;
        }
        status = "httpd (no pid file) not running";
    }
    else {
        have_pid_file = 1;
        if (kill(otherpid, 0) == 0) {
            running = 1;
            status = apr_psprintf(pconf, 
                                  "httpd (pid %" APR_PID_T_FMT ") already "
                                  "running", otherpid);
        }
        else {
            status = apr_psprintf(pconf,
                                  "httpd (pid %" APR_PID_T_FMT "?) not running",
