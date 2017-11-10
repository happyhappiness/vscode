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

    if (r) {
        AP_DEBUG_ASSERT(r->connection != NULL);
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
                info.module_index = A