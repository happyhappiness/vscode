                             "Parent: Cannot create restart event %s", signal_restart_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            CleanNullACL((void *)sa);

            /* Now that we are flying at 15000 feet...
             * wipe out the Win95 service console,
             * signal the SCM the WinNT service started, or
             * if not a service, setup console handlers instead.
             */
            if (!strcasecmp(signal_arg, "runservice"))
            {
                if (osver.dwPlatformId != VER_PLATFORM_WIN32_NT)
                {
                    rv = mpm_service_to_start(&service_name,
                                              s->process->pool);
                    if (rv != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                                     "%s: Unable to start the service manager.",
                                     service_name);
                        return HTTP_INTERNAL_SERVER_ERROR;
                    }
                }
            }

            /* Create the start mutex, as an unnamed object for security.
             * Ths start mutex is used during a restart to prevent more than
             * one child process from entering the accept loop at once.
             */
            rv =  apr_proc_mutex_create(&start_mutex, NULL,
                                        APR_LOCK_DEFAULT,
