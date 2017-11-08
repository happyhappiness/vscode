static const char *set_dbm_type(cmd_parms *cmd, 
                                void *dir_config, 
                                const char *arg)
{
    dbm_auth_config_rec *conf = dir_config;
   
    conf->auth_dbmtype = apr_pstrdup(cmd->pool, arg);
    return NULL;
}