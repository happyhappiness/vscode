                ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                             "%s: Unable to create the start_mutex.",
                             service_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
    }
    else /* parent_pid != my_pid */
    {
        mpm_start_child_console_handler();
    }
    return OK;
