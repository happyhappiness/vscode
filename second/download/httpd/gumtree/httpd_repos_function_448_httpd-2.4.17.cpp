static const char *add_custom_log(cmd_parms *cmd, void *dummy, const char *fn,
                                  const char *fmt, const char *envclause)
{
    const char *err_string = NULL;
    multi_log_state *mls = ap_get_module_config(cmd->server->module_config,
                                                &log_config_module);
    config_log_state *cls;

    cls = (config_log_state *) apr_array_push(mls->config_logs);
    cls->condition_var = NULL;
    cls->condition_expr = NULL;
    if (envclause != NULL) {
        if (strncasecmp(envclause, "env=", 4) == 0) {
            if ((envclause[4] == '\0')
                || ((envclause[4] == '!') && (envclause[5] == '\0'))) {
                return "missing environment variable name";
            }
            cls->condition_var = apr_pstrdup(cmd->pool, &envclause[4]);
        }
        else if (strncasecmp(envclause, "expr=", 5) == 0) {
            const char *err;
            if ((envclause[5] == '\0'))
                return "missing condition";
            cls->condition_expr = ap_expr_parse_cmd(cmd, &envclause[5],
                                                    AP_EXPR_FLAG_DONT_VARY,
                                                    &err, NULL);
            if (err)
                return err;
        }
        else {
            return "error in condition clause";
        }
    }

    cls->fname = fn;
    cls->format_string = fmt;
    cls->directive = cmd->directive;
    if (fmt == NULL) {
        cls->format = NULL;
    }
    else {
        cls->format = parse_log_string(cmd->pool, fmt, &err_string);
    }
    cls->log_writer = NULL;

    return err_string;
}