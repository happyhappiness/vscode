static const char *set_undefined_echo(cmd_parms *cmd, void *mconfig, const char *msg)
{
    include_server_config *conf;
    conf = ap_get_module_config(cmd->server->module_config, &include_module);
    conf->undefinedEcho = apr_pstrdup(cmd->pool, msg);
    conf->undefinedEchoLen = strlen(msg);

    return NULL;
}