
    unixd_set_rlimit(cmd, &conf->limit_nproc, arg, arg2, RLIMIT_NPROC);
    return NULL;
}
#endif

static const char *set_recursion_limit(cmd_parms *cmd, void *dummy,
                                       const char *arg1, const char *arg2)
{
    core_server_config *conf = ap_get_module_config(cmd->server->module_config,
                                                    &core_module);
    int limit = atoi(arg1);

    if (limit <= 0) {
        return "The recursion limit must be greater than zero.";
    }
    if (limit < 4) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Limiting internal redirects to very low numbers may "
                     "cause normal requests to fail.");
    }

    conf->redirect_limit = limit;

    if (arg2) {
        limit = atoi(arg2);

        if (limit <= 0) {
            return "The recursion limit must be greater than zero.";
        }
        if (limit < 4) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "Limiting the subrequest depth to a very low level may"
                         " cause normal requests to fail.");
        }
    }

    conf->subreq_limit = limit;

    return NULL;
}

static void log_backtrace(const request_rec *r)
{
    const request_rec *top = r;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "r->uri = %s", r->uri ? r->uri : "(unexpectedly NULL)");

    while (top && (top->prev || top->main)) {
        if (top->prev) {
            top = top->prev;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "redirected from r->uri = %s",
                          top->uri ? top->uri : "(unexpectedly NULL)");
        }

        if (!top->prev && top->main) {
            top = top->main;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "subrequested from r->uri = %s",
                          top->uri ? top->uri : "(unexpectedly NULL)");
        }
    }
}

/*
 * check whether redirect limit is reached
 */
AP_DECLARE(int) ap_is_recursion_limit_exceeded(const request_rec *r)
{
    core_server_config *conf = ap_get_module_config(r->server->module_config,
                                                    &core_module);
    const request_rec *top = r;
    int redirects = 0, subreqs = 0;
    int rlimit = conf->redirect_limit
                 ? conf->redirect_limit
                 : AP_DEFAULT_MAX_INTERNAL_REDIRECTS;
    int slimit = conf->subreq_limit
                 ? conf->subreq_limit
                 : AP_DEFAULT_MAX_SUBREQ_DEPTH;


    while (top->prev || top->main) {
        if (top->prev) {
            if (++redirects >= rlimit) {
                /* uuh, too much. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Request exceeded the limit of %d internal "
                              "redirects due to probable configuration error. "
                              "Use 'LimitInternalRecursion' to increase the "
                              "limit if necessary. Use 'LogLevel debug' to get "
                              "a backtrace.", rlimit);

                /* post backtrace */
                log_backtrace(r);

                /* return failure */
                return 1;
            }

            top = top->prev;
        }

        if (!top->prev && top->main) {
            if (++subreqs >= slimit) {
                /* uuh, too much. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Request exceeded the limit of %d subrequest "
                              "nesting levels due to probable confguration "
                              "error. Use 'LimitInternalRecursion' to increase "
                              "the limit if necessary. Use 'LogLevel debug' to "
                              "get a backtrace.", slimit);

                /* post backtrace */
                log_backtrace(r);

                /* return failure */
                return 1;
            }

            top = top->main;
        }
    }

    /* recursion state: ok */
    return 0;
}

static const char *add_ct_output_filters(cmd_parms *cmd, void *conf_,
                                         const char *arg, const char *arg2)
{
    core_dir_config *conf = conf_;
    ap_filter_rec_t *old, *new = NULL;
    const char *filter_name;
