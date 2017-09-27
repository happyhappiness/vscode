
    argv0 = apr_filepath_name_get(r->filename);
    nph = !(strncmp(argv0, "nph-", 4));
    conf = ap_get_module_config(r->server->module_config, &cgi_module);

    if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r))
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "Options ExecCGI is off in this directory");
    if (nph && is_included)
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "attempt to include NPH CGI script");

    if (r->finfo.filetype == APR_NOFILE)
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                               "script not found or unable to stat");
    if (r->finfo.filetype == APR_DIR)
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "attempt to invoke directory as script");

    if ((r->used_path_info == AP_REQ_REJECT_PATH_INFO) &&
        r->path_info && *r->path_info)
    {
        /* default to accept */
        return log_scripterror(r, conf, HTTP_NOT_FOUND, 0,
                               "AcceptPathInfo off disallows user's path");
    }
/*
    if (!ap_suexec_enabled) {
        if (!ap_can_exec(&r->finfo))
            return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
