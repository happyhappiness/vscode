static void log_error_core(const char *file, int line, int level,
                           apr_status_t status, const server_rec *s,
                           const request_rec *r, apr_pool_t *pool,
                           const char *fmt, va_list args)
{
    char errstr[MAX_STRING_LEN];
    apr_size_t len, errstrlen;
    apr_file_t *logf = NULL;
    const char *referer;
    int level_and_mask = level & APLOG_LEVELMASK;

    if (s == NULL) {
        /*
         * If we are doing stderr logging (startup), don't log messages that are
         * above the default server log level unless it is a startup/shutdown
         * notice
         */
        if ((level_and_mask != APLOG_NOTICE)
            && (level_and_mask > ap_default_loglevel)) {
            return;
        }

        logf = stderr_log;
    }
    else if (s->error_log) {
        /*
         * If we are doing normal logging, don't log messages that are
         * above the server log level unless it is a startup/shutdown notice
         */
        if ((level_and_mask != APLOG_NOTICE)
            && (level_and_mask > s->loglevel)) {
            return;
        }

        logf = s->error_log;
    }
#ifdef TPF
    else if (tpf_child) {
        /*
         * If we are doing normal logging, don't log messages that are
         * above the server log level unless it is a startup/shutdown notice
         */
        if ((level_and_mask != APLOG_NOTICE)
            && (level_and_mask > s->loglevel)) {
            return;
        }

        logf = stderr;
    }
#endif /* TPF */
    else {
        /*
         * If we are doing syslog logging, don't log messages that are
         * above the server log level (including a startup/shutdown notice)
         */
        if (level_and_mask > s->loglevel) {
            return;
        }
    }

    if (logf && ((level & APLOG_STARTUP) != APLOG_STARTUP)) {
        errstr[0] = '[';
        ap_recent_ctime(errstr + 1, apr_time_now());
        errstr[1 + APR_CTIME_LEN - 1] = ']';
        errstr[1 + APR_CTIME_LEN    ] = ' ';
        len = 1 + APR_CTIME_LEN + 1;
    } else {
        len = 0;
    }

    if ((level & APLOG_STARTUP) != APLOG_STARTUP) {
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            "[%s] ", priorities[level_and_mask].t_name);
    }

#ifndef TPF
    if (file && level_and_mask == APLOG_DEBUG) {
#ifdef _OSD_POSIX
        char tmp[256];
        char *e = strrchr(file, '/');

        /* In OSD/POSIX, the compiler returns for __FILE__
         * a string like: __FILE__="*POSIX(/usr/include/stdio.h)"
         * (it even returns an absolute path for sources in
         * the current directory). Here we try to strip this
         * down to the basename.
         */
        if (e != NULL && e[1] != '\0') {
            apr_snprintf(tmp, sizeof(tmp), "%s", &e[1]);
            e = &tmp[strlen(tmp)-1];
            if (*e == ')') {
                *e = '\0';
            }
            file = tmp;
        }
#endif /*_OSD_POSIX*/
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            "%s(%d): ", file, line);
    }
#endif /* TPF */

    if (r && r->connection) {
        /* XXX: TODO: add a method of selecting whether logged client
         * addresses are in dotted quad or resolved form... dotted
         * quad is the most secure, which is why I'm implementing it
         * first. -djg
         */
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            "[client %s] ", r->connection->remote_ip);
    }
    if (status != 0) {
        char buf[120];
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            "(%d)%s: ", status,
                            apr_strerror(status, buf, sizeof(buf)));
    }
    errstrlen = len;
    len += apr_vsnprintf(errstr + len, MAX_STRING_LEN - len, fmt, args);

    if (r && (referer = apr_table_get(r->headers_in, "Referer"))) {
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            ", referer: %s", referer);
    }

    /* NULL if we are logging to syslog */
    if (logf) {
        /* Truncate for the terminator (as apr_snprintf does) */
        if (len > MAX_STRING_LEN - sizeof(APR_EOL_STR)) {
            len = MAX_STRING_LEN - sizeof(APR_EOL_STR);
        }
        strcpy(errstr + len, APR_EOL_STR);
        apr_file_puts(errstr, logf);
        apr_file_flush(logf);
    }
#ifdef HAVE_SYSLOG
    else {
        syslog(level_and_mask, "%s", errstr);
    }
#endif

    ap_run_error_log(file, line, level, status, s, r, pool, errstr + errstrlen);
}