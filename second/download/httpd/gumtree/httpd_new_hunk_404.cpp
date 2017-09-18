    parms.server = s;
    parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
    parms.limited = -1;

    errmsg = ap_walk_config(conftree, &parms, s->lookup_defaults);
    if (errmsg) {
        ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
                     "Syntax error on line %d of %s:",
                     parms.err_directive->line_num,
                     parms.err_directive->filename);
        ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
                     "%s", errmsg);
        exit(1);
    }
}

AP_CORE_DECLARE(int) ap_parse_htaccess(ap_conf_vector_t **result,
