
    arr_param->curr_idx = arr_param->array->nelts;

    return 0;
}

static void process_command_config(server_rec *s, apr_array_header_t *arr,
                                   ap_directive_t **conftree, apr_pool_t *p,
                                   apr_pool_t *ptemp)
{
    const char *errmsg;
    cmd_parms parms;
    arr_elts_param_t arr_parms;

    arr_parms.curr_idx = 0;
    arr_parms.array = arr;

    parms = default_parms;
    parms.pool = p;
    parms.temp_pool = ptemp;
    parms.server = s;
    parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);

    parms.config_file = ap_pcfg_open_custom(p, "-c/-C directives",
                                            &arr_parms, NULL,
                                            arr_elts_getstr, arr_elts_close);

    errmsg = ap_build_config(&parms, p, ptemp, conftree);
    if (errmsg) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Syntax error in -C/-c directive:");
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s", errmsg);
        exit(1);
    }

    ap_cfg_closefile(parms.config_file);
}

typedef struct {
    char *fname;
} fnames;

