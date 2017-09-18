            if (errno == ECONNREFUSED && connect_tries < DEFAULT_CONNECT_ATTEMPTS) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, errno, r,
                              "connect #%d to cgi daemon failed, sleeping before retry",
                              connect_tries);
                close(sd);
                apr_sleep(sliding_timer);
                if (sliding_timer < 2 * APR_USEC_PER_SEC) {
                    sliding_timer *= 2;
                }
            }
            else {
                close(sd);
                return log_scripterror(r, conf, HTTP_SERVICE_UNAVAILABLE, errno, 
