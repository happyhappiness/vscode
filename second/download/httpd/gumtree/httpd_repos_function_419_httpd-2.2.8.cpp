static const char *log_format(cmd_parms *cmd, void *dummy, const char *fmt,
                              const char *name)
{
    const char *err_string = NULL;
    multi_log_state *mls = ap_get_module_config(cmd->server->module_config,
                                                &log_config_module);

    /*
     * If we were given two arguments, the second is a name to be given to the
     * format.  This syntax just defines the nickname - it doesn't actually
     * make the format the default.
     */
    if (name != NULL) {
        parse_log_string(cmd->pool, fmt, &err_string);
        if (err_string == NULL) {
            apr_table_setn(mls->formats, name, fmt);
        }
    }
    else {
        mls->default_format_string = fmt;
        mls->default_format = parse_log_string(cmd->pool, fmt, &err_string);
    }
    return err_string;
}