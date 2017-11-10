static const char *set_bind_password(cmd_parms *cmd, void *_cfg, const char *arg)
{
    authn_ldap_config_t *sec = _cfg;
    int arglen = strlen(arg);
    char **argv;
    char *result;

    if ((arglen > 5) && strncmp(arg, "exec:", 5) == 0) {
        if (apr_tokenize_to_argv(arg+5, &argv, cmd->temp_pool) != APR_SUCCESS) {
            return apr_pstrcat(cmd->pool,
                               "Unable to parse exec arguments from ",
                               arg+5, NULL);
        }
        argv[0] = ap_server_root_relative(cmd->temp_pool, argv[0]);

        if (!argv[0]) {
            return apr_pstrcat(cmd->pool,
                               "Invalid AuthLDAPBindPassword exec location:",
                               arg+5, NULL);
        }
        result = ap_get_exec_line(cmd->pool,
                                  (const char*)argv[0], (const char * const *)argv);

        if(!result) {
            return apr_pstrcat(cmd->pool,
                               "Unable to get bind password from exec of ",
                               arg+5, NULL);
        }
        sec->bindpw = result;
    }
    else {
        sec->bindpw = (char *)arg;
    }

    return NULL;
}