static const char *set_dbmtype(cmd_parms *cmd,
                               void *dconf,
                               const char *arg)
{
    express_server_conf *sconf;
    sconf = ap_get_module_config(cmd->server->module_config, &proxy_express_module);

    sconf->dbmtype = arg;

    return NULL;
}