static const char *unset_define(cmd_parms *cmd, void *dummy,
                                const char *name)
{
    int i;
    char **defines;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    if (ap_strchr_c(name, ':') != NULL)
        return "Variable name must not contain ':'";

    if (!saved_server_config_defines)
        init_config_defines(cmd->pool);

    defines = (char **)ap_server_config_defines->elts;
    for (i = 0; i < ap_server_config_defines->nelts; i++) {
        if (strcmp(defines[i], name) == 0) {
            defines[i] = *(char **)apr_array_pop(ap_server_config_defines);
            break;
        }
    }

    if (server_config_defined_vars) {
        apr_table_unset(server_config_defined_vars, name);
    }

    return NULL;
}