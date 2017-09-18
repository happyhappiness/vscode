            break;
        }
    }
    return errstr;
}

void ssl_log(server_rec *s, int level, const char *msg, ...)
{
    char tstr[80];
    char lstr[256];
    char vstr[1024];
    char str[1024];
    char *nstr;
    apr_size_t len;
    apr_time_exp_t t;
    va_list ap;
    int add;
    int i;
    char *astr;
    int safe_errno;
    unsigned long e;
    SSLSrvConfigRec *sc;
    char *cpE;
    char *cpA;

    /*  initialization  */
    safe_errno = errno;
    sc = mySrvConfig(s);

    /*  strip out additional flags  */
    add   = (level & ~SSL_LOG_MASK);
    level = (level & SSL_LOG_MASK);

    /*  reduce flags when not reasonable in context  */
    if (add & SSL_ADD_ERRNO && errno == 0)
        add &= ~SSL_ADD_ERRNO;
    if (add & SSL_ADD_SSLERR && ERR_peek_error() == 0)
        add &= ~SSL_ADD_SSLERR;

    /*  we log only levels below, except for errors */
    if (   sc->log_file == NULL
        && !(level & SSL_LOG_ERROR))
        return;
    if (   level > sc->log_level
        && !(level & SSL_LOG_ERROR))
        return;

    /*  determine the time entry string  */
    if (add & SSL_NO_TIMESTAMP)
        tstr[0] = NUL;
    else {
        apr_time_exp_lt(&t, apr_time_now());
        apr_strftime(tstr, &len, 80, "[%d/%b/%Y %H:%M:%S", &t);
        apr_snprintf(tstr + strlen(tstr), 80 - strlen(tstr), " %05d] ", 
                     (unsigned int)getpid());
    }

    /*  determine whether newline should be written */
    if (add & SSL_NO_NEWLINE)
        nstr = "";
    else {
        nstr = APR_EOL_STR;
    }

    /*  determine level name  */
    lstr[0] = NUL;
    if (!(add & SSL_NO_LEVELID)) {
        for (i = 0; ssl_log_level2string[i].nLevel != 0; i++) {
            if (ssl_log_level2string[i].nLevel == level) {
                apr_snprintf(lstr, sizeof(lstr), "[%s]", ssl_log_level2string[i].szLevel);
                break;
            }
        }
        for (i = strlen(lstr); i <= 7; i++)
            lstr[i] = ' ';
        lstr[i] = NUL;
    }

    if (add & SSL_INIT) {
        len = strlen(lstr);
        apr_snprintf(&lstr[len], sizeof(lstr) - len,
                     "Init: (%s) ", sc->vhost_id);
    }

    /*  create custom message  */
    va_start(ap, msg);
    apr_vsnprintf(vstr, sizeof(vstr), msg, ap);
    va_end(ap);

    /*  write out SSLog message  */
    if ((add & SSL_ADD_ERRNO) && (add & SSL_ADD_SSLERR))
        astr = " (System and " SSL_LIBRARY_NAME " library errors follow)";
    else if (add & SSL_ADD_ERRNO)
        astr = " (System error follows)";
    else if (add & SSL_ADD_SSLERR)
        astr = " (" SSL_LIBRARY_NAME " library error follows)";
    else
        astr = "";
    if (level <= sc->log_level && sc->log_file != NULL) {
        apr_snprintf(str, sizeof(str), "%s%s%s%s%s", 
                     tstr, lstr, vstr, astr, nstr);
        apr_file_printf(sc->log_file, "%s", str);
    }
    if (level & SSL_LOG_ERROR)
        ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                     "mod_ssl: %s%s", vstr, astr);

    /*  write out additional attachment messages  */
    if (add & SSL_ADD_ERRNO) {
        if (level <= sc->log_level && sc->log_file != NULL) {
            apr_snprintf(str, sizeof(str), "%s%sSystem: %s (errno: %d)%s",
                         tstr, lstr, strerror(safe_errno), safe_errno, nstr);
            apr_file_printf(sc->log_file, "%s", str);
        }
        if (level & SSL_LOG_ERROR)
            ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                         "System: %s (errno: %d)",
                         strerror(safe_errno), safe_errno);
    }
    if (add & SSL_ADD_SSLERR) {
        while ((e = ERR_get_error())) {
            cpE = ERR_error_string(e, NULL);
            cpA = ssl_log_annotation(cpE);
            if (level <= sc->log_level && sc->log_file != NULL) {
                apr_snprintf(str, sizeof(str), "%s%s%s: %s%s%s%s%s",
                             tstr, lstr, SSL_LIBRARY_NAME, cpE,
                             cpA != NULL ? " [Hint: " : "",
                             cpA != NULL ? cpA : "", cpA != NULL ? "]" : "",
                             nstr);
                apr_file_printf(sc->log_file, "%s", str);
            }
            if (level & SSL_LOG_ERROR)
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                             "%s: %s%s%s%s", SSL_LIBRARY_NAME, cpE,
                             cpA != NULL ? " [Hint: " : "",
                             cpA != NULL ? cpA : "", cpA != NULL ? "]" : "");
        }
    }
    /* make sure the next log starts from a clean base */
    /* ERR_clear_error(); */

    /*  cleanup and return  */
    if (sc->log_file != NULL)
        apr_file_flush(sc->log_file);
    errno = safe_errno;
    return;
}

void ssl_die(void)
{
    /*
     * This is used for fatal errors and here
     * it is common module practice to really
     * exit from the complete program.
     */
    exit(1);
}

