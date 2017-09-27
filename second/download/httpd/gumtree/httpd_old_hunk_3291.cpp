        /* On Unix, __FILE__ may be an absolute path in a
         * VPATH build. */
        if (file[0] == '/' && (p = ap_strrchr_c(file, '/')) != NULL) {
            file = p + 1;
        }
#endif /*_OSD_POSIX || WIN32 */
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            "%s(%d): ", file, line);
    }

    if (c) {
        /* XXX: TODO: add a method of selecting whether logged remote
         * addresses are in dotted quad or resolved form... dotted
         * quad is the most secure, which is why I'm implementing it
         * first. -djg
         */
        /*
         * remote_ip can be client or backend server. If we have a scoreboard
         * handle, it is likely a client.
         */
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            c->sbh ? "[client %s:%d] " : "[remote %s:%d] ",
                            c->remote_ip, c->remote_addr->port);
    }
    if (status != 0) {
        if (status < APR_OS_START_EAIERR) {
            len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                                "(%d)", status);
        }
        else if (status < APR_OS_START_SYSERR) {
            len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                                "(EAI %d)", status - APR_OS_START_EAIERR);
        }
        else if (status < 100000 + APR_OS_START_SYSERR) {
            len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                                "(OS %d)", status - APR_OS_START_SYSERR);
        }
        else {
            len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                                "(os 0x%08x)", status - APR_OS_START_SYSERR);
        }
        apr_strerror(status, errstr + len, MAX_STRING_LEN - len);
        len += strlen(errstr + len);
        if (MAX_STRING_LEN - len > 2) {
            errstr[len++] = ':';
            errstr[len++] = ' ';
            errstr[len] = '\0';
        }
    }

    errstrlen = len;
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    if (apr_vsnprintf(scratch, MAX_STRING_LEN - len, fmt, args)) {
        len += ap_escape_errorlog_item(errstr + len, scratch,
                                       MAX_STRING_LEN - len);
    }
#else
    len += apr_vsnprintf(errstr + len, MAX_STRING_LEN - len, fmt, args);
#endif

    if (   r && (referer = apr_table_get(r->headers_in, "Referer"))
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
        && ap_escape_errorlog_item(scratch, referer, MAX_STRING_LEN - len)
#endif
        ) {
        len += apr_snprintf(errstr + len, MAX_STRING_LEN - len,
                            ", referer: %s",
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
                            scratch
#else
                            referer
#endif
                            );
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
        syslog(level_and_mask < LOG_PRIMASK ? level_and_mask : APLOG_DEBUG,
               "%s", errstr);
    }
#endif

    ap_run_error_log(file, line, module_index, level, status, s, r, pool,
                     errstr + errstrlen);
}

AP_DECLARE(void) ap_log_error_(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const server_rec *s, const char *fmt, ...)
{
