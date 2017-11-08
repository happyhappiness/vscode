static const char *set_dbmfile(cmd_parms *cmd,
                               void *dconf,
                               const char *arg)
{
    express_server_conf *sconf;
    sconf = ap_get_module_config(cmd->server->module_config, &proxy_express_module);

    if ((sconf->dbmfile = ap_server_root_relative(cmd->pool, arg)) == NULL) {
        return apr_pstrcat(cmd->pool, "ProxyExpressDBMFile: bad path to file: ",
                           arg, NULL);
    }
    return NULL;
}