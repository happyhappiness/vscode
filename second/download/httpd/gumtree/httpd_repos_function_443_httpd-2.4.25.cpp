static const char *add_global_log(cmd_parms *cmd, void *dummy, const char *fn,
                                  const char *fmt, const char *envclause) {
    multi_log_state *mls = ap_get_module_config(cmd->server->module_config,
                                                &log_config_module);
    config_log_state *clsarray;
    config_log_state *cls;
    const char *ret;

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err) {
        return err;
    }

    /* Add a custom log through the normal channel */
    ret = add_custom_log(cmd, dummy, fn, fmt, envclause);

    /* Set the inherit flag unless there was some error */
    if (ret == NULL) {
        clsarray = (config_log_state*)mls->config_logs->elts;
        cls = &clsarray[mls->config_logs->nelts-1];
        cls->inherit = 1;
    }

    return ret;
}