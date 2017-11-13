static int open_error_log(server_rec *s, int is_main, apr_pool_t *p)
{
    const char *fname;
    int rc;

    if (*s->error_fname == '|') {
        apr_file_t *dummy = NULL;
        apr_cmdtype_e cmdtype = APR_SHELLCMD_ENV;
        fname = s->error_fname + 1;

        /* In 2.4 favor PROGRAM_ENV, accept "||prog" syntax for compatibility
         * and "|$cmd" to override the default.
         * Any 2.2 backport would continue to favor SHELLCMD_ENV so there 
         * accept "||prog" to override, and "|$cmd" to ease conversion.
         */
        if (*fname == '|') {
            cmdtype = APR_PROGRAM_ENV;
            ++fname;
        }
        if (*fname == '$')
            ++fname;
	
        /* Spawn a new child logger.  If this is the main server_rec,
         * the new child must use a dummy stderr since the current
         * stderr might be a pipe to the old logger.  Otherwise, the
         * child inherits the parents stderr. */
        rc = log_child(p, fname, &dummy, cmdtype, is_main);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "Couldn't start ErrorLog process");
            return DONE;
        }

        s->error_log = dummy;
    }

#ifdef HAVE_SYSLOG
    else if (!strncasecmp(s->error_fname, "syslog", 6)) {
        if ((fname = strchr(s->error_fname, ':'))) {
            const TRANS *fac;

            fname++;
            for (fac = facilities; fac->t_name; fac++) {
                if (!strcasecmp(fname, fac->t_name)) {
                    openlog(ap_server_argv0, LOG_NDELAY|LOG_CONS|LOG_PID,
                            fac->t_val);
                    s->error_log = NULL;
                    return OK;
                }
            }
        }
        else {
            openlog(ap_server_argv0, LOG_NDELAY|LOG_CONS|LOG_PID, LOG_LOCAL7);
        }

        s->error_log = NULL;
    }
#endif
    else {
        fname = ap_server_root_relative(p, s->error_fname);
        if (!fname) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, APR_EBADPATH, NULL,
                         "%s: Invalid error log path %s.",
                         ap_server_argv0, s->error_fname);
            return DONE;
        }
        if ((rc = apr_file_open(&s->error_log, fname,
                               APR_APPEND | APR_WRITE | APR_CREATE | APR_LARGEFILE,
                               APR_OS_DEFAULT, p)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "%s: could not open error log file %s.",
                         ap_server_argv0, fname);
            return DONE;
        }
    }

    return OK;
}