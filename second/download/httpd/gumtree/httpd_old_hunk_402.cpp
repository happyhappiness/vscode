    parms.config_file = ap_pcfg_open_custom(p, "-c/-C directives",
                                            &arr_parms, NULL,
                                            arr_elts_getstr, arr_elts_close);

    errmsg = ap_build_config(&parms, p, ptemp, conftree);
    if (errmsg) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                     "Syntax error in -C/-c directive:" APR_EOL_STR "%s",
                     errmsg);
        exit(1);
    }

    ap_cfg_closefile(parms.config_file);
