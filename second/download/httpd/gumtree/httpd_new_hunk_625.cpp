                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "%s: Unable to create the start_mutex.",
                             service_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }            
        }
        /* Always reset our console handler to be the first, even on a restart
        *  because some modules (e.g. mod_perl) might have set a console 
        *  handler to terminate the process.
        */
        if (strcasecmp(signal_arg, "runservice"))
            mpm_start_console_handler();
    }
    else /* parent_pid != my_pid */
    {
        mpm_start_child_console_handler();
    }
    return OK;
