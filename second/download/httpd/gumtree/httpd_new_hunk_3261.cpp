        d->override &= ~OR_UNSET;
    }

    return NULL;
}

static const char *set_override_list(cmd_parms *cmd, void *d_, int argc, char *const argv[])
{
    core_dir_config *d = d_;
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

static const char *set_options(cmd_parms *cmd, void *d_, const char *l)
{
    core_dir_config *d = d_;
    allow_options_t opt;
    int first = 1;
    int merge = 0;
    int all_none = 0;
    char action;

    while (l[0]) {
        char *w = ap_getword_conf(cmd->temp_pool, &l);
        action = '\0';

        if (*w == '+' || *w == '-') {
            action = *(w++);
            if (!merge && !first && !all_none) {
                return "Either all Options must start with + or -, or no Option may.";
            }
            merge = 1;
        }
        else if (first) {
            d->opts = OPT_NONE;
        }
        else if (merge) {
            return "Either all Options must start with + or -, or no Option may.";
        }

        if (!strcasecmp(w, "Indexes")) {
            opt = OPT_INDEXES;
        }
        else if (!strcasecmp(w, "Includes")) {
