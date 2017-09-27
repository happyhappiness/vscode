         *
         * XXX: Could just write first time through too, although
         *      that may screw up scripts written to do something
         *      based on the last modification time of the pid file.
         */
        ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, p,
                      apr_psprintf(p, "pid file %s overwritten -- Unclean "
                                   "shutdown of previous Apache run?",
                                   fname));
    }

    if ((rv = apr_file_open(&pid_file, fname,
                            APR_WRITE | APR_CREATE | APR_TRUNCATE,
                            APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD, p))
        != APR_SUCCESS) {
