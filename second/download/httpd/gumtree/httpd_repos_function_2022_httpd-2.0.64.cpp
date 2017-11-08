int ap_signal_server(int *exit_status, apr_pool_t *pconf)
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
                                  otherpid);
        }
    }

    if (!strcmp(dash_k_arg, "start")) {
        if (running) {
            printf("%s\n", status);
            return 1;
        }
    }

    if (!strcmp(dash_k_arg, "stop")) {
        if (!running) {
            printf("%s\n", status);
        }
        else {
            send_signal(otherpid, SIGTERM);
        }
        return 1;
    }

    if (!strcmp(dash_k_arg, "restart")) {
        if (!running) {
            printf("httpd not running, trying to start\n");
        }
        else {
            *exit_status = send_signal(otherpid, SIGHUP);
            return 1;
        }
    }

    if (!strcmp(dash_k_arg, "graceful")) {
        if (!running) {
            printf("httpd not running, trying to start\n");
        }
        else {
            *exit_status = send_signal(otherpid, SIGUSR1);
            return 1;
        }
    }

    return 0;
}