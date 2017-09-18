         * Only warn on first time through for this pid.
         *
         * XXX: Could just write first time through too, although
         *      that may screw up scripts written to do something
         *      based on the last modification time of the pid file.
         */
        ap_log_perror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, p,
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
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, NULL,
                     "%s: could not log pid to file %s",
                     ap_server_argv0, fname);
        exit(1);
    }
    apr_file_printf(pid_file, "%ld" APR_EOL_STR, (long)mypid);
    apr_file_close(pid_file);
    saved_pid = mypid;
}

AP_DECLARE(void) ap_log_assert(const char *szExp, const char *szFile,
                               int nLine)
{
    char time_str[APR_CTIME_LEN];

    apr_ctime(time_str, apr_time_now());
    ap_log_error(APLOG_MARK, APLOG_CRIT | APLOG_NOERRNO, 0, NULL,
                 "[%s] file %s, line %d, assertion \"%s\" failed",
                 time_str, szFile, nLine, szExp);
#if defined(WIN32)
    DebugBreak();
#else
    /* unix assert does an abort leading to a core dump */
