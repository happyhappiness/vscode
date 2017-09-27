            if (APR_SUCCESS == rs) {
                gotlock = 1;
                break; /* Out of the loop */
            }
            else {
                /* Some error, log and bail */
                ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server,
                             "Child %ld failed to acquire lock",
                             (long int)getpid());
                break; /* Out of the loop without having the lock */
            }
        }
        else {
            /* Some other error, log and bail */
            ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server,
                         "Child %ld failed to try and acquire lock",
                         (long int)getpid());
            break; /* Out of the loop without having the lock */
        }

        /*
         * The only way to get to this point is if the trylock worked
         * and returned BUSY. So, bump the time and try again
         */
        timecamped += CAMPOUT;
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, r->server,
                     "Child %ld camping out on mutex for %" APR_INT64_T_FMT
                     " microseconds",
                     (long int) getpid(), timecamped);
    } /* Lock acquisition loop */

    /* Sleep for a millisecond to make it a little harder for
