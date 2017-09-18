                           ap_valid_accept_mutex_string, NULL);
    }
    return NULL;
}

#endif

#ifdef AP_MPM_WANT_SIGNAL_SERVER

static const char *dash_k_arg;

static int send_signal(pid_t pid, int sig)
{
    if (kill(pid, sig) < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, errno, NULL,
                     "sending signal to server");
        return 1;
    }
    return 0;
}

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

void ap_mpm_rewrite_args(process_rec *process)
{
    apr_array_header_t *mpm_new_argv;
    apr_status_t rv;
    apr_getopt_t *opt;
    char optbuf[3];
    const char *optarg;
    int fixed_args;

    mpm_new_argv = apr_array_make(process->pool, process->argc,
                                  sizeof(const char **));
    *(const char **)apr_array_push(mpm_new_argv) = process->argv[0];
    fixed_args = mpm_new_argv->nelts;
    apr_getopt_init(&opt, process->pool, process->argc, process->argv);
    opt->errfn = NULL;
    optbuf[0] = '-';
    /* option char returned by apr_getopt() will be stored in optbuf[1] */
    optbuf[2] = '\0';
    while ((rv = apr_getopt(opt, "k:" AP_SERVER_BASEARGS,
                            optbuf + 1, &optarg)) == APR_SUCCESS) {
        switch(optbuf[1]) {
        case 'k':
            if (!dash_k_arg) {
                if (!strcmp(optarg, "start") || !strcmp(optarg, "stop") ||
                    !strcmp(optarg, "restart") || !strcmp(optarg, "graceful")) {
                    dash_k_arg = optarg;
                    break;
                }
            }
        default:
            *(const char **)apr_array_push(mpm_new_argv) =
                apr_pstrdup(process->pool, optbuf);
            if (optarg) {
                *(const char **)apr_array_push(mpm_new_argv) = optarg;
            }
        }
    }

    /* back up to capture the bad argument */
    if (rv == APR_BADCH || rv == APR_BADARG) {
        opt->ind--;
    }

    while (opt->ind < opt->argc) {
        *(const char **)apr_array_push(mpm_new_argv) =
            apr_pstrdup(process->pool, opt->argv[opt->ind++]);
    }

    process->argc = mpm_new_argv->nelts;
    process->argv = (const char * const *)mpm_new_argv->elts;

    if (dash_k_arg) {
        APR_REGISTER_OPTIONAL_FN(ap_signal_server);
    }
}

#endif /* AP_MPM_WANT_SIGNAL_SERVER */

