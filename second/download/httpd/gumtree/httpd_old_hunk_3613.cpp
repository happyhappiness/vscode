AP_INIT_TAKE1("ScriptLogBuffer", set_scriptlog_buffer, NULL, RSRC_CONF,
     "the maximum size (in bytes) to record of a POST request"),
    {NULL}
};

static int log_scripterror(request_rec *r, cgi_server_conf * conf, int ret,
                           apr_status_t rv, char *error)
{
    apr_file_t *f = NULL;
    apr_finfo_t finfo;
    char time_str[APR_CTIME_LEN];
    int log_flags = rv ? APLOG_ERR : APLOG_ERR;

    ap_log_rerror(APLOG_MARK, log_flags, rv, r,
                  "%s: %s", error, r->filename);

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname ||
        ((apr_stat(&finfo, conf->logname,
                   APR_FINFO_SIZE, r->pool) == APR_SUCCESS) &&
         (finfo.size > conf->logbytes)) ||
