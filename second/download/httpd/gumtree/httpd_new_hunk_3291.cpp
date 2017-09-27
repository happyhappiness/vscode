        /* On Unix, __FILE__ may be an absolute path in a
         * VPATH build. */
        if (file[0] == '/' && (p = ap_strrchr_c(file, '/')) != NULL) {
            file = p + 1;
        }
#endif /*_OSD_POSIX || WIN32 */
        return apr_snprintf(buf, buflen, "%s(%d)", file, info->line);
    }
}

static int log_apr_status(const ap_errorlog_info *info, const char *arg,
                          char *buf, int buflen)
{
    apr_status_t status = info->status;
    int len;
    if (!status)
        return 0;

    if (status < APR_OS_START_EAIERR) {
        len = apr_snprintf(buf, buflen, "(%d)", status);
    }
    else if (status < APR_OS_START_SYSERR) {
        len = apr_snprintf(buf, buflen, "(EAI %d)",
                           status - APR_OS_START_EAIERR);
    }
    else if (status < 100000 + APR_OS_START_SYSERR) {
        len = apr_snprintf(buf, buflen, "(OS %d)",
                           status - APR_OS_START_SYSERR);
    }
    else {
        len = apr_snprintf(buf, buflen, "(os 0x%08x)",
                           status - APR_OS_START_SYSERR);
    }
    apr_strerror(status, buf + len, buflen - len);
    len += strlen(buf + len);
    return len;
}

static int log_server_name(const ap_errorlog_info *info, const char *arg,
                           char *buf, int buflen)
{
    if (info->r)
        return cpystrn(buf, ap_get_server_name((request_rec *)info->r), buflen);

    return 0;
}

static int log_virtual_host(const ap_errorlog_info *info, const char *arg,
                            char *buf, int buflen)
{
    if (info->s)
        return cpystrn(buf, info->s->server_hostname, buflen);

    return 0;
}


static int log_table_entry(const apr_table_t *table, const char *name,
                           char *buf, int buflen)
{
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    const char *value;
    char scratch[MAX_STRING_LEN];

    if ((value = apr_table_get(table, name)) != NULL) {
        ap_escape_errorlog_item(scratch, value, MAX_STRING_LEN);
        return cpystrn(buf, scratch, buflen);
    }

    return 0;
#else
    return cpystrn(buf, apr_table_get(table, name), buflen);
#endif
}

static int log_header(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    if (info->r)
        return log_table_entry(info->r->headers_in, arg, buf, buflen);

    return 0;
}

static int log_note(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    /* XXX: maybe escaping the entry is not necessary for notes? */
    if (info->r)
        return log_table_entry(info->r->notes, arg, buf, buflen);

    return 0;
}

static int log_env_var(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    if (info->r)
        return log_table_entry(info->r->subprocess_env, arg, buf, buflen);

    return 0;
}

static int core_generate_log_id(const conn_rec *c, const request_rec *r,
                                 const char **idstring)
{
    apr_uint64_t id, tmp;
    pid_t pid;
    int len;
    char *encoded;

    if (r && r->request_time) {
        id = (apr_uint64_t)r->request_time;
    }
    else {
        id = (apr_uint64_t)apr_time_now();
    }

    pid = getpid();
    if (sizeof(pid_t) > 2) {
        tmp = pid;
        tmp = tmp << 40;
        id ^= tmp;
        pid = pid >> 24;
        tmp = pid;
        tmp = tmp << 56;
        id ^= tmp;
    }
    else {
        tmp = pid;
        tmp = tmp << 40;
        id ^= tmp;
    }
#if APR_HAS_THREADS
    {
        apr_uintptr_t tmp2 = (apr_uintptr_t)c->current_thread;
        tmp = tmp2;
        tmp = tmp << 32;
        id ^= tmp;
    }
#endif

    len = apr_base64_encode_len(sizeof(id)); /* includes trailing \0 */
    encoded = apr_palloc(r ? r->pool : c->pool, len);
    apr_base64_encode(encoded, (char *)&id, sizeof(id));

    /* Skip the last char, it is always '=' */
    encoded[len - 2] = '\0';

    *idstring = encoded;

    return OK;
}

static void add_log_id(const conn_rec *c, const request_rec *r)
{
    const char **id;
    /* need to cast const away */
    if (r) {
        id = &((request_rec *)r)->log_id;
    }
    else {
        id = &((conn_rec *)c)->log_id;
    }

    ap_run_generate_log_id(c, r, id);
}

AP_DECLARE(void) ap_register_log_hooks(apr_pool_t *p)
{
    ap_hook_generate_log_id(core_generate_log_id, NULL, NULL,
                            APR_HOOK_REALLY_LAST);

    ap_register_errorlog_handler(p, "a", log_remote_address, 0);
    ap_register_errorlog_handler(p, "A", log_local_address, 0);
    ap_register_errorlog_handler(p, "e", log_env_var, 0);
    ap_register_errorlog_handler(p, "E", log_apr_status, 0);
    ap_register_errorlog_handler(p, "F", log_file_line, 0);
    ap_register_errorlog_handler(p, "i", log_header, 0);
    ap_register_errorlog_handler(p, "k", log_keepalives, 0);
    ap_register_errorlog_handler(p, "l", log_loglevel, 0);
    ap_register_errorlog_handler(p, "L", log_log_id, 0);
    ap_register_errorlog_handler(p, "m", log_module_name, 0);
    ap_register_errorlog_handler(p, "n", log_note, 0);
    ap_register_errorlog_handler(p, "P", log_pid, 0);
    ap_register_errorlog_handler(p, "t", log_ctime, 0);
    ap_register_errorlog_handler(p, "T", log_tid, 0);
    ap_register_errorlog_handler(p, "v", log_virtual_host, 0);
    ap_register_errorlog_handler(p, "V", log_server_name, 0);
}

/*
 * This is used if no error log format is defined and during startup.
 * It automatically omits the timestamp if logging to syslog.
 */
static int do_errorlog_default(const ap_errorlog_info *info, char *buf,
                               int buflen, int *errstr_start, int *errstr_end,
                               const char *errstr_fmt, va_list args)
{
    int len = 0;
    int field_start = 0;
    int item_len;
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    char scratch[MAX_STRING_LEN];
#endif

    if (!info->using_syslog && !info->startup) {
        buf[len++] = '[';
        len += log_ctime(info, "u", buf + len, buflen - len);
        buf[len++] = ']';
        buf[len++] = ' ';
    }

    if (!info->startup) {
        buf[len++] = '[';
        len += log_module_name(info, NULL, buf + len, buflen - len);
        buf[len++] = ':';
        len += log_loglevel(info, NULL, buf + len, buflen - len);
        len += cpystrn(buf + len, "] [pid ", buflen - len);

        len += log_pid(info, NULL, buf + len, buflen - len);
#if APR_HAS_THREADS
        field_start = len;
        len += cpystrn(buf + len, ":tid ", buflen - len);
        item_len = log_tid(info, NULL, buf + len, buflen - len);
        if (!item_len)
            len = field_start;
        else
            len += item_len;
#endif
        buf[len++] = ']';
        buf[len++] = ' ';
    }

    if (info->level >= APLOG_DEBUG) {
        item_len = log_file_line(info, NULL, buf + len, buflen - len);
        if (item_len) {
            len += item_len;
            len += cpystrn(buf + len, ": ", buflen - len);
        }
    }

    if (info->status) {
        item_len = log_apr_status(info, NULL, buf + len, buflen - len);
        if (item_len) {
            len += item_len;
            len += cpystrn(buf + len, ": ", buflen - len);
        }
    }

    /*
     * useragent_ip/client_ip can be client or backend server. If we have
     * a scoreboard handle, it is likely a client.
     */
    if (info->r) {
        len += apr_snprintf(buf + len, buflen - len,
                            info->r->connection->sbh ? "[client %s:%d] " : "[remote %s:%d] ",
                            info->r->useragent_ip, info->r->useragent_addr->port);
    }
    else if (info->c) {
        len += apr_snprintf(buf + len, buflen - len,
                            info->c->sbh ? "[client %s:%d] " : "[remote %s:%d] ",
                            info->c->client_ip, info->c->client_addr->port);
    }

    /* the actual error message */
    *errstr_start = len;
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    if (apr_vsnprintf(scratch, MAX_STRING_LEN, errstr_fmt, args)) {
        len += ap_escape_errorlog_item(buf + len, scratch,
                                       buflen - len);

    }
#else
    len += apr_vsnprintf(buf + len, buflen - len, errstr_fmt, args);
#endif
    *errstr_end = len;

    field_start = len;
    len += cpystrn(buf + len, ", referer: ", buflen - len);
    item_len = log_header(info, "Referer", buf + len, buflen - len);
    if (item_len)
        len += item_len;
    else
        len = field_start;

    return len;
}

static int do_errorlog_format(apr_array_header_t *fmt, ap_errorlog_info *info,
                              char *buf, int buflen, int *errstr_start,
                              int *errstr_end, const char *err_fmt, va_list args)
{
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
    char scratch[MAX_STRING_LEN];
#endif
    int i;
    int len = 0;
    int field_start = 0;
    int skipping = 0;
    ap_errorlog_format_item *items = (ap_errorlog_format_item *)fmt->elts;

    for (i = 0; i < fmt->nelts; ++i) {
        ap_errorlog_format_item *item = &items[i];
        if (item->flags & AP_ERRORLOG_FLAG_FIELD_SEP) {
            if (skipping) {
                skipping = 0;
            }
            else {
                field_start = len;
            }
        }

        if (item->flags & AP_ERRORLOG_FLAG_MESSAGE) {
            /* the actual error message */
            *errstr_start = len;
#ifndef AP_UNSAFE_ERROR_LOG_UNESCAPED
            if (apr_vsnprintf(scratch, MAX_STRING_LEN, err_fmt, args)) {
                len += ap_escape_errorlog_item(buf + len, scratch,
                                               buflen - len);

            }
#else
            len += apr_vsnprintf(buf + len, buflen - len, err_fmt, args);
#endif
            *errstr_end = len;
        }
        else if (skipping) {
            continue;
        }
        else if (info->level != -1 && (int)item->min_loglevel > info->level) {
            len = field_start;
            skipping = 1;
        }
        else {
            int item_len = (*item->func)(info, item->arg, buf + len,
                                         buflen - len);
            if (!item_len) {
                if (item->flags & AP_ERRORLOG_FLAG_REQUIRED) {
                    /* required item is empty. skip whole line */
                    buf[0] = '\0';
                    return 0;
                }
                else if (item->flags & AP_ERRORLOG_FLAG_NULL_AS_HYPHEN) {
                    buf[len++] = '-';
                }
                else {
                    len = field_start;
                    skipping = 1;
                }
            }
            else {
                len += item_len;
            }
        }
    }
    return len;
}

static void write_logline(char *errstr, apr_size_t len, apr_file_t *logf,
                          int level)
{
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
        syslog(level < LOG_PRIMASK ? level : APLOG_DEBUG, "%s", errstr);
    }
#endif
}

static void log_error_core(const char *file, int line, int module_index,
                           int level,
                           apr_status_t status, const server_rec *s,
                           const conn_rec *c,
                           const request_rec *r, apr_pool_t *pool,
                           const char *fmt, va_list args)
{
    char errstr[MAX_STRING_LEN];
    apr_file_t *logf = NULL;
    int level_and_mask = level & APLOG_LEVELMASK;
    const request_rec *rmain = NULL;
    core_server_config *sconf = NULL;
    ap_errorlog_info info;

    /* do we need to log once-per-req or once-per-conn info? */
    int log_conn_info = 0, log_req_info = 0;
    apr_array_header_t **lines = NULL;
    int done = 0;
    int line_number = 0;

    if (r && r->connection) {
        c = r->connection;
    }

    if (s == NULL) {
        /*
         * If we are doing stderr logging (startup), don't log messages that are
         * above the default server log level unless it is a startup/shutdown
         * notice
         */
#ifndef DEBUG
        if ((level_and_mask != APLOG_NOTICE)
            && (level_and_mask > ap_default_loglevel)) {
            return;
        }
#endif

        logf = stderr_log;
    }
    else {
        int configured_level = r ? ap_get_request_module_loglevel(r, module_index)        :
                               c ? ap_get_conn_server_module_loglevel(c, s, module_index) :
                                   ap_get_server_module_loglevel(s, module_index);
        if (s->error_log) {
            /*
             * If we are doing normal logging, don't log messages that are
             * above the module's log level unless it is a startup/shutdown notice
             */
            if ((level_and_mask != APLOG_NOTICE)
                && (level_and_mask > configured_level)) {
                return;
            }

            logf = s->error_log;
        }
        else {
            /*
             * If we are doing syslog logging, don't log messages that are
             * above the module's log level (including a startup/shutdown notice)
             */
            if (level_and_mask > configured_level) {
                return;
            }
        }

        /* the faked server_rec from mod_cgid does not have s->module_config */
        if (s->module_config) {
            sconf = ap_get_core_module_config(s->module_config);
            if (c && !c->log_id) {
                add_log_id(c, NULL);
                if (sconf->error_log_conn && sconf->error_log_conn->nelts > 0)
                    log_conn_info = 1;
            }
            if (r) {
                if (r->main)
                    rmain = r->main;
                else
                    rmain = r;

                if (!rmain->log_id) {
                    /* XXX: do we need separate log ids for subrequests? */
                    if (sconf->error_log_req && sconf->error_log_req->nelts > 0)
                        log_req_info = 1;
                    /*
                     * XXX: potential optimization: only create log id if %L is
                     * XXX: actually used
                     */
                    add_log_id(c, rmain);
                }
            }
        }
    }

    info.s             = s;
    info.c             = c;
    info.pool          = pool;
    info.file          = NULL;
    info.line          = 0;
    info.status        = 0;
    info.using_syslog  = (logf == NULL);
    info.startup       = ((level & APLOG_STARTUP) == APLOG_STARTUP);
    info.format        = fmt;

    while (!done) {
        apr_array_header_t *log_format;
        int len = 0, errstr_start = 0, errstr_end = 0;
        /* XXX: potential optimization: format common prefixes only once */
        if (log_conn_info) {
            /* once-per-connection info */
            if (line_number == 0) {
                lines = (apr_array_header_t **)sconf->error_log_conn->elts;
                info.r = NULL;
                info.rmain = NULL;
                info.level = -1;
                info.module_index = APLOG_NO_MODULE;
            }

            log_format = lines[line_number++];

            if (line_number == sconf->error_log_conn->nelts) {
                /* this is the last line of once-per-connection info */
                line_number = 0;
                log_conn_info = 0;
            }
        }
        else if (log_req_info) {
            /* once-per-request info */
            if (line_number == 0) {
                lines = (apr_array_header_t **)sconf->error_log_req->elts;
                info.r = rmain;
                info.rmain = rmain;
                info.level = -1;
                info.module_index = APLOG_NO_MODULE;
            }

            log_format = lines[line_number++];

            if (line_number == sconf->error_log_req->nelts) {
                /* this is the last line of once-per-request info */
                line_number = 0;
                log_req_info = 0;
            }
        }
        else {
            /* the actual error message */
            info.r            = r;
            info.rmain        = rmain;
            info.level        = level_and_mask;
            info.module_index = module_index;
            info.file         = file;
            info.line         = line;
            info.status       = status;
            log_format = sconf ? sconf->error_log_format : NULL;
            done = 1;
        }

        /*
         * prepare and log one line
         */

        if (log_format) {
            len += do_errorlog_format(log_format, &info, errstr + len,
                                      MAX_STRING_LEN - len,
                                      &errstr_start, &errstr_end, fmt, args);
        }
        else {
            len += do_errorlog_default(&info, errstr + len, MAX_STRING_LEN - len,
                                       &errstr_start, &errstr_end, fmt, args);
        }

        if (!*errstr)
        {
            /*
             * Don't log empty lines. This can happen with once-per-conn/req
             * info if an item with AP_ERRORLOG_FLAG_REQUIRED is NULL.
             */
            continue;
        }
        write_logline(errstr, len, logf, level_and_mask);

        if (done) {
            /*
             * We don't call the error_log hook for per-request/per-conn
             * lines, and we only pass the actual log message, not the
             * prefix and suffix.
             */
            errstr[errstr_end] = '\0';
            ap_run_error_log(&info, errstr + errstr_start);
        }

        *errstr = '\0';
    }
}

AP_DECLARE(void) ap_log_error_(const char *file, int line, int module_index,
                               int level, apr_status_t status,
                               const server_rec *s, const char *fmt, ...)
{
