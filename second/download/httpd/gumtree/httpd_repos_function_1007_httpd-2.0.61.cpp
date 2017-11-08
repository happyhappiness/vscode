static void rewritelog(request_rec *r, int level, const char *text, ...)
{
    rewrite_server_conf *conf;
    conn_rec *conn;
    char *str1;
    char str2[512];
    char str3[1024];
    const char *type;
    char redir[20]; /* enough for "/redir#%d" if int is 32 bit */
    va_list ap;
    int i;
    apr_size_t nbytes;
    request_rec *req;
    char *ruser;
    const char *rhost;
    apr_status_t rv;

    va_start(ap, text);
    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
    conn = r->connection;

    if (conf->rewritelogfp == NULL) {
        return;
    }
    if (conf->rewritelogfile == NULL) {
        return;
    }
    if (*(conf->rewritelogfile) == '\0') {
        return;
    }

    if (level > conf->rewriteloglevel) {
        return;
    }

    if (r->user == NULL) {
        ruser = "-";
    }
    else if (strlen(r->user) != 0) {
        ruser = r->user;
    }
    else {
        ruser = "\"\"";
    }

    rhost = ap_get_remote_host(conn, r->per_dir_config,
                               REMOTE_NOLOOKUP, NULL);
    if (rhost == NULL) {
        rhost = "UNKNOWN-HOST";
    }

    str1 = apr_pstrcat(r->pool, rhost, " ",
                      (conn->remote_logname != NULL ?
                      conn->remote_logname : "-"), " ",
                      ruser, NULL);
    apr_vsnprintf(str2, sizeof(str2), text, ap);

    if (r->main == NULL) {
        type = "initial";
    }
    else {
        type = "subreq";
    }

    for (i = 0, req = r; req->prev != NULL; req = req->prev) {
        i++;
    }
    if (i == 0) {
        redir[0] = '\0';
    }
    else {
        apr_snprintf(redir, sizeof(redir), "/redir#%d", i);
    }

    apr_snprintf(str3, sizeof(str3),
                "%s %s [%s/sid#%lx][rid#%lx/%s%s] (%d) %s" APR_EOL_STR, str1,
                current_logtime(r), ap_get_server_name(r),
                (unsigned long)(r->server), (unsigned long)r,
                type, redir, level, str2);

    rv = apr_global_mutex_lock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_lock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }
    nbytes = strlen(str3);
    apr_file_write(conf->rewritelogfp, str3, &nbytes);
    rv = apr_global_mutex_unlock(rewrite_log_lock);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "apr_global_mutex_unlock(rewrite_log_lock) failed");
        /* XXX: Maybe this should be fatal? */
    }

    va_end(ap);
    return;
}