static const char *cmd_rewriteloglevel(cmd_parms *cmd, void *dconf,
                                       const char *a1)
{
    rewrite_server_conf *sconf;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
    sconf->rewriteloglevel = atoi(a1);

    return NULL;
}