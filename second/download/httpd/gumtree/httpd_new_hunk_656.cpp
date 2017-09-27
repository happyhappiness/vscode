        return DECLINED;

    is_included = !strcmp(r->protocol, "INCLUDED");

    p = r->main ? r->main->pool : r->pool;

    argv0 = apr_filepath_name_get(r->filename);
    nph = !(strncmp(argv0, "nph-", 4));
    conf = ap_get_module_config(r->server->module_config, &cgi_module);

    if (!(ap_allow_options(r) & OPT_EXECCGI) && !is_scriptaliased(r))
        return log_scripterror(r, conf, HTTP_FORBIDDEN, 0,
                               "Options ExecCGI is off in this directory");
