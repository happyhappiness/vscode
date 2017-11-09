static const char *set_define(cmd_parms *cmd, void *dummy,
                              const char *name, const char *value)
{
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    if (ap_strchr_c(name, ':') != NULL)
        return "Variable name must not contain ':'";

    if (!saved_server_config_defines)
        init_config_defines(cmd->pool);
    if (!ap_exists_config_define(name)) {
        char **newv = (char **)apr_array_push(ap_server_config_defines);
        *newv = apr_pstrdup(cmd->pool, name);
    }
    if (value) {
        if (!server_config_defined_vars)
            server_config_defined_vars = apr_table_make(cmd->pool, 5);
        apr_table_setn(server_config_defined_vars, name, value);
    }

    return NULL;
}