static const char *cmd_rewritelog(cmd_parms *cmd, void *dconf, const char *a1)
{
    rewrite_server_conf *sconf;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    sconf->rewritelogfile = a1;

    return NULL;
}