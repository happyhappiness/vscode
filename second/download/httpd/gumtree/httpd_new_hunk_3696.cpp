     * and platforms where trylock works.
     */
    for (camped = 0, timecamped = 0; camped < MAXCAMP; camped++) {
        rs = apr_global_mutex_trylock(exipc_mutex);
        if (APR_STATUS_IS_EBUSY(rs)) {
            apr_sleep(CAMPOUT);
        }
        else if (APR_SUCCESS == rs) {
            gotlock = 1;
            break; /* Get out of the loop */
        }
        else if (APR_STATUS_IS_ENOTIMPL(rs)) {
            /* If it's not implemented, just hang in the mutex. */
            startcamp = apr_time_now();
            rs = apr_global_mutex_lock(exipc_mutex);
            timecamped = (apr_int64_t) (apr_time_now() - startcamp);
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
