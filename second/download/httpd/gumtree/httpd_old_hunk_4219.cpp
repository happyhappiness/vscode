    int i;
    const char *err;

    /* Throw a warning if we're in <Location> or <Files> */
    if (ap_check_cmd_context(cmd, NOT_IN_LOCATION | NOT_IN_FILES)) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00115)
                     "Useless use of AllowOverrideList in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);
    }
    if ((err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS)) != NULL)
        return err;

    d->override_list = apr_table_make(cmd->pool, 1);

    for (i=0;i<argc;i++){
        if (!strcasecmp(argv[i], "None")) {
            return NULL;
        }
        else {
            const command_rec *result = NULL;
            module *mod = ap_top_module;
            result = ap_find_command_in_modules(argv[i], &mod);
            if (result)
                apr_table_set(d->override_list, argv[i], "1");
            else
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00116)
                             "Discarding unrecognized directive `%s' in AllowOverrideList.",
                             argv[i]);
        }
    }

    return NULL;
}

