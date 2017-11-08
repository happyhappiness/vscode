static const char *add_custom_log(cmd_parms *cmd, void *dummy, const char *fn,
                                  const char *fmt, const char *envclause)
{
    const char *err_string = NULL;
    multi_log_state *mls = ap_get_module_config(cmd->server->module_config,
						&log_config_module);
    config_log_state *cls;

    cls = (config_log_state *) apr_array_push(mls->config_logs);
    cls->condition_var = NULL;
    if (envclause != NULL) {
	if (strncasecmp(envclause, "env=", 4) != 0) {
	    return "error in condition clause";
	}
	if ((envclause[4] == '\0')
	    || ((envclause[4] == '!') && (envclause[5] == '\0'))) {
	    return "missing environment variable name";
	}
	cls->condition_var = apr_pstrdup(cmd->pool, &envclause[4]);
    }

    cls->fname = fn;
    cls->format_string = fmt;
    if (fmt == NULL) {
        cls->format = NULL;
    }
    else {
        cls->format = parse_log_string(cmd->pool, fmt, &err_string);
    }
    cls->log_writer = NULL;

    return err_string;
}