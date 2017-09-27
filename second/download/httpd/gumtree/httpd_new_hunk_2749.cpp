    stat = sock_read(sd, &pid, sizeof(pid));
    if (stat != APR_SUCCESS) {
        return stat;
    }

    if (pid == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, info->r, APLOGNO(01261)
                      "daemon couldn't find CGI process for connection %lu",
                      info->conn_id);
        return APR_EGENERAL;
    }
    return cleanup_nonchild_process(info->r, pid);
}

static int cgid_handler(request_rec *r)
{
    int retval, nph, dbpos;
    char *argv0, *dbuf;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    cgid_server_conf *conf;
    int is_included;
    int seen_eos, child_stopped_reading;
    int sd;
    char **env;
    apr_file_t *tempsock;
    struct cleanup_script_info *info;
    apr_status_t rv;

    if (strcmp(r->handler, CGI_MAGIC_TYPE) && strcmp(r->handler, "cgi-script")) {
        return DECLINED;
    }

    conf = ap_get_module_config(r->server->module_config, &cgid_module);
    is_included = !strcmp(r->protocol, "INCLUDED");

    if ((argv0 = strrchr(r->filename, '/')) != NULL) {
        argv0++;
    }
    else {
        argv0 = r->filename;
    }

    nph = !(strncmp(argv0, "nph-", 4));

    argv0 = r->filename;

    if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r)) {
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, APLOGNO(01262)
                "Options ExecCGI is off in this directory");
    }

    if (nph && is_included) {
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, APLOGNO(01263)
                "attempt to include NPH CGI script");
    }

#if defined(OS2) || defined(WIN32)
#error mod_cgid does not work on this platform.  If you teach it to, look
#error at mod_cgi.c for required code in this path.
#else
    if (r->finfo.filetype == APR_NOFILE) {
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0, APLOGNO(01264)
                "script not found or unable to stat");
    }
#endif
    if (r->finfo.filetype == APR_DIR) {
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, APLOGNO(01265)
                "attempt to invoke directory as script");
    }

    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info)
    {
        /* default to accept */
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0, APLOGNO(01266)
                               "AcceptPathInfo off disallows user's path");
    }
/*
    if (!ap_suexec_enabled) {
        if (!ap_can_exec(&r->finfo))
            return log_scripterror(r, conf, HTTP_FORBIDDEN, 0, APLOGNO(01267)
                                   "file permissions deny server execution");
    }
*/
    ap_add_common_vars(r);
    ap_add_cgi_vars(r);
    env = ap_create_environment(r->pool, r->subprocess_env);
