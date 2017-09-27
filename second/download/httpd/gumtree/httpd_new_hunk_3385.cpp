             * at once.
             */
            if (num_completion_contexts >= max_num_completion_contexts) {
                /* All workers are busy, need to wait for one */
                static int reported = 0;
                if (!reported) {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00326)
                                 "Server ran out of threads to serve "
                                 "requests. Consider raising the "
                                 "ThreadsPerChild setting");
                    reported = 1;
                }

