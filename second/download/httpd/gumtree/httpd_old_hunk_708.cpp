                        * the network is up again, and restart the children.
                        * Ben Hyde noted that temporary ENETDOWN situations
                        * occur in mobile IP.
                        */
                        ap_log_error(APLOG_MARK, APLOG_EMERG, stat, ap_server_conf,
                            "apr_accept: giving up.");
                        apr_thread_mutex_unlock(accept_mutex);
                        clean_child_exit(APEXIT_CHILDFATAL, my_worker_num, ptrans, bucket_alloc);

                    default:
                        ap_log_error(APLOG_MARK, APLOG_ERR, stat, ap_server_conf,
                            "apr_accept: (client socket)");
                        apr_thread_mutex_unlock(accept_mutex);
                        clean_child_exit(1, my_worker_num, ptrans, bucket_alloc);
                }
            }
        }

        /* Unlock the mutext so that the next thread can start listening for requests. */
        apr_thread_mutex_unlock(accept_mutex);

        ap_create_sb_handle(&sbh, ptrans, 0, my_worker_num);
        /*
        * We now have a connection, so set it up with the appropriate
        * socket options, file descriptors, and read/write buffers.
        */
        current_conn = ap_run_create_connection(ptrans, ap_server_conf, csd, 
