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