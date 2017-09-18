                        * Ben Hyde noted that temporary ENETDOWN situations
                        * occur in mobile IP.
                        */
                        ap_log_error(APLOG_MARK, APLOG_EMERG, stat, ap_server_conf,
                            "apr_accept: giving up.");
                        clean_child_exit(APEXIT_CHILDFATAL, my_worker_num, ptrans, bucket_alloc);
    
                    default:
                        ap_log_error(APLOG_MARK, APLOG_ERR, stat, ap_server_conf,
                            "apr_accept: (client socket)");
                        clean_child_exit(1, my_worker_num, ptrans, bucket_alloc);
                }
            }
        }
