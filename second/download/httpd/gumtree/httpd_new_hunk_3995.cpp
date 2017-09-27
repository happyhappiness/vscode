{
    apr_file_t *f = NULL;
    struct stat finfo;
    char time_str[APR_CTIME_LEN];
    int log_flags = rv ? APLOG_ERR : APLOG_ERR;

    /* Intentional no APLOGNO */
    /* Callee provides APLOGNO in error text */
    ap_log_rerror(APLOG_MARK, log_flags, rv, r,
                "%s: %s", error, r->filename);

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname ||
        ((stat(conf->logname, &finfo) == 0)
