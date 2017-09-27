                             "Parent: Cannot create restart event %s", signal_restart_name);
                CleanNullACL((void *)sa);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            CleanNullACL((void *)sa);

            /* Create the start mutex, as an unnamed object for security.
             * Ths start mutex is used during a restart to prevent more than
             * one child process from entering the accept loop at once.
             */
            rv =  apr_proc_mutex_create(&start_mutex, NULL,
                                        APR_LOCK_DEFAULT,
