                                              s->process->pool);
                    if (rv != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                     "%s: Unable to start the service manager.",
                                     service_name);
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }
                }
            }
            else /* ! -k runservice */
            {
                mpm_start_console_handler();
            }

            /* Create the start mutex, as an unnamed object for security.
             * Ths start mutex is used during a restart to prevent more than 
             * one child process from entering the accept loop at once.
             */
            rv =  apr_proc_mutex_create(&start_mutex, NULL,
                                        APR_LOCK_DEFAULT,
                                        ap_server_conf->process->pool);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "%s: Unable to create the start_mutex.",
                             service_name);
