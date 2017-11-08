static const char *set_default_end_tag(cmd_parms *cmd, void *mconfig, const char *msg)
{
    include_server_config *conf;
    conf= ap_get_module_config(cmd->server->module_config , &include_module);
    conf->default_end_tag = apr_pstrdup(cmd->pool, msg);

    return NULL;
}