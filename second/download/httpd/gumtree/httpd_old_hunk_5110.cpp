            /* Exit event was signaled */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00357)
                         "Child: Exit event signaled. Child process is "
                         "ending.");
            break;
        }
        else {
            /* MaxConnectionsPerChild event set by the worker threads.
             * Signal the parent to restart
             */
            ap_log_error(APLOG_MARK, APLOG_NOTICE, APR_SUCCESS, ap_server_conf, APLOGNO(00358)
                         "Child: Process exiting because it reached "
