static int log_scripterror(request_rec *r, cgid_server_conf * conf, int ret,
                           apr_status_t rv, char *error)
{
    apr_file_t *f = NULL;
    struct stat finfo;
    char time_str[APR_CTIME_LEN];
    int log_flags = rv ? APLOG_ERR : APLOG_ERR;

    ap_log_rerror(APLOG_MARK, log_flags, rv, r,
                "%s: %s", error, r->filename);

    /* XXX Very expensive mainline case! Open, then getfileinfo! */
    if (!conf->logname ||
        ((stat(conf->logname, &finfo) == 0)
         && (finfo.st_size > conf->logbytes)) ||
         (apr_file_open(&f, conf->logname,
                  APR_APPEND|APR_WRITE|APR_CREATE, APR_OS_DEFAULT, r->pool) != APR_SUCCESS)) {
        return ret;
    }

    /* "%% [Wed Jun 19 10:53:21 1996] GET /cgid-bin/printenv HTTP/1.0" */
    apr_ctime(time_str, apr_time_now());
    apr_file_printf(f, "%%%% [%s] %s %s%s%s %s\n", time_str, r->method, r->uri,
            r->args ? "?" : "", r->args ? r->args : "", r->protocol);
    /* "%% 500 /usr/local/apache/cgid-bin */
    apr_file_printf(f, "%%%% %d %s\n", ret, r->filename);

    apr_file_printf(f, "%%error\n%s\n", error);

    apr_file_close(f);
    return ret;
}