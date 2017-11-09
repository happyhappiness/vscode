static const char *set_enabled(cmd_parms *cmd,
                               void *dconf,
                               int flag)
{
    express_server_conf *sconf;
    sconf = ap_get_module_config(cmd->server->module_config, &proxy_express_module);

    sconf->enabled = flag;

    return NULL;
}