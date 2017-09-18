         * Only warn on first time through for this pid.
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
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                     "could not create %s", fname);
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "%s: could not log pid to file %s",
                     ap_server_argv0, fname);
        exit(1);
    }
    apr_file_printf(pid_file, "%ld" APR_EOL_STR, (long)mypid);
    apr_file_close(pid_file);
    saved_pid = mypid;
}

AP_DECLARE(apr_status_t) ap_read_pid(apr_pool_t *p, const char *filename,
                                     pid_t *mypid)
{
    const apr_size_t BUFFER_SIZE = sizeof(long) * 3 + 2; /* see apr_ltoa */
    apr_file_t *pid_file = NULL;
    apr_status_t rv;
    const char *fname;
    char *buf, *endptr;
    apr_size_t bytes_read;

    if (!filename) {
        return APR_EGENERAL;
    }

    fname = ap_server_root_relative(p, filename);
    if (!fname) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, APR_EBADPATH, 
                     NULL, "Invalid PID file path %s, ignoring.", filename);
        return APR_EGENERAL;
    }

    rv = apr_file_open(&pid_file, fname, APR_READ, APR_OS_DEFAULT, p);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    /* Ensure null-termination, so that strtol doesn't go crazy. */
    buf = apr_palloc(p, BUFFER_SIZE);
    buf[BUFFER_SIZE - 1] = '\0';

    rv = apr_file_read_full(pid_file, buf, BUFFER_SIZE - 1, &bytes_read);
    if (rv != APR_SUCCESS && rv != APR_EOF) {
        return rv;
    }

    /* If we fill the buffer, we're probably reading a corrupt pid file.
     * To be nice, let's also ensure the first char is a digit. */
    if (bytes_read == BUFFER_SIZE - 1 || !apr_isdigit(*buf)) {
        return APR_EGENERAL;
    }

    *mypid = strtol(buf, &endptr, 10);

    apr_file_close(pid_file);
    return APR_SUCCESS;
}

AP_DECLARE(void) ap_log_assert(const char *szExp, const char *szFile,
                               int nLine)
{
    char time_str[APR_CTIME_LEN];

    apr_ctime(time_str, apr_time_now());
    ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                 "[%s] file %s, line %d, assertion \"%s\" failed",
                 time_str, szFile, nLine, szExp);
#if defined(WIN32)
    DebugBreak();
#else
    /* unix assert does an abort leading to a core dump */
