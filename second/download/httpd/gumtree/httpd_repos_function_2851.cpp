static const char *set_define(cmd_parms *cmd, void *dummy,
                              const char *optarg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    if (!ap_exists_config_define(optarg)) {
        char **newv = (char **)apr_array_push(ap_server_config_defines);
        *newv = apr_pstrdup(cmd->pool, optarg);
    }

    return NULL;
}