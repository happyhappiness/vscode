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

    if ((retval = connect_to_daemon(&sd, r, conf)) != OK) {
        return retval;
