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

