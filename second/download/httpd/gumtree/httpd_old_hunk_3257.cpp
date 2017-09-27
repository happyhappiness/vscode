}

static const char *set_access_name(cmd_parms *cmd, void *dummy,
                                   const char *arg)
{
    void *sconf = cmd->server->module_config;
    core_server_config *conf = ap_get_module_config(sconf, &core_module);

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    conf->access_name = apr_pstrdup(cmd->pool, arg);
    return NULL;
}


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

static const char *unset_define(cmd_parms *cmd, void *dummy,
                                const char *optarg)
{
    int i;
    char **defines;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    defines = (char **)ap_server_config_defines->elts;
    for (i = 0; i < ap_server_config_defines->nelts; i++) {
        if (strcmp(defines[i], optarg) == 0) {
            defines[i] = apr_array_pop(ap_server_config_defines);
            break;
        }
    }

    return NULL;
}

#ifdef GPROF
static const char *set_gprof_dir(cmd_parms *cmd, void *dummy, const char *arg)
{
    void *sconf = cmd->server->module_config;
    core_server_config *conf = ap_get_module_config(sconf, &core_module);

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    conf->gprof_dir = apr_pstrdup(cmd->pool, arg);
    return NULL;
}
#endif /*GPROF*/

static const char *set_add_default_charset(cmd_parms *cmd,
                                           void *d_, const char *arg)
