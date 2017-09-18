static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret, 
                           apr_status_t rv, char *error) 
{ 
    apr_file_t *f = NULL; 
    struct stat finfo; 
    char time_str[APR_CTIME_LEN];
    int log_flags = rv ? APLOG_ERR : APLOG_NOERRNO | APLOG_ERR;

    ap_log_rerror(APLOG_MARK, log_flags, rv, r, 
                "%s: %s", error, r->filename); 

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname || 
