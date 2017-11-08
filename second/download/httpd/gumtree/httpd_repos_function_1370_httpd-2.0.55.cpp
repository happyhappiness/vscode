static const char *set_default_time_fmt(cmd_parms *cmd, void *mconfig, const char *fmt)
{
    include_dir_config *conf = (include_dir_config *)mconfig;
    conf->default_time_fmt = apr_pstrdup(cmd->pool, fmt);
    return NULL;
}