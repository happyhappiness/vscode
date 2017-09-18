                exit(0);
            }

            rv = mpm_merge_service_args(process->pool, mpm_new_argv, 
                                        fixed_args);
            if (rv == APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_NOERRNO|APLOG_INFO, 0, NULL,
                             "Using ConfigArgs of the installed service "
                             "\"%s\".", service_name);
            }
            else  {
                ap_log_error(APLOG_MARK,APLOG_WARNING, rv, NULL,
                             "No installed ConfigArgs for the service "
