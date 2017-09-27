}

static void log_backtrace(const request_rec *r)
{
    const request_rec *top = r;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00121)
                  "r->uri = %s", r->uri ? r->uri : "(unexpectedly NULL)");

    while (top && (top->prev || top->main)) {
        if (top->prev) {
            top = top->prev;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00122)
                          "redirected from r->uri = %s",
                          top->uri ? top->uri : "(unexpectedly NULL)");
        }

        if (!top->prev && top->main) {
            top = top->main;
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00123)
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
    core_server_config *conf =
        ap_get_core_module_config(r->server->module_config);
    const request_rec *top = r;
    int redirects = 0, subreqs = 0;
    int rlimit = conf->redirect_limit
                 ? conf->redirect_limit
                 : AP_DEFAULT_MAX_INTERNAL_REDIRECTS;
    int slimit = conf->subreq_limit
