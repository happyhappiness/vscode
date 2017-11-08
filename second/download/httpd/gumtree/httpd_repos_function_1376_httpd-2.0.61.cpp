static const char *set_default_error_msg(cmd_parms *cmd, void *mconfig, const char *msg)
{
    include_dir_config *conf = (include_dir_config *)mconfig;
    conf->default_error_msg = apr_pstrdup(cmd->pool, msg);
    return NULL;
}