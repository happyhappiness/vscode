        strcpy(errstr + len, APR_EOL_STR);
        apr_file_puts(errstr, logf);
        apr_file_flush(logf);
    }
#ifdef HAVE_SYSLOG
    else {
        syslog(level < LOG_PRIMASK ? level : APLOG_DEBUG, "%.*s",
               (int)len, errstr);
    }
#endif
}

static void log_error_core(const char *file, int line, int module_index,
                           int level,
