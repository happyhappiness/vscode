    parms.pool = p;
    parms.temp_pool = ptemp;
    parms.server = s;
    parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);

    if (ap_pcfg_openfile(&cfp, p, fname) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: could not open document config file %s",
                     ap_server_argv0, fname);
        exit(1);
    }

    parms.config_file = cfp;

    errmsg = ap_build_config(&parms, p, ptemp, conftree);

    if (errmsg != NULL) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Syntax error on line %d of %s:",
                     parms.err_directive->line_num,
                     parms.err_directive->filename);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s", errmsg);
        exit(1);
    }

    ap_cfg_closefile(cfp);
}
