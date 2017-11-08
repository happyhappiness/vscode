static const char *set_dbm_type(cmd_parms *cmd,
                                void *dir_config,
                                const char *arg)
{
    authn_dbm_config_rec *conf = dir_config;

    conf->dbmtype = apr_pstrdup(cmd->pool, arg);
    return NULL;
}