static const char *header_name_set(cmd_parms *cmd, void *dummy,
                                   const char *arg)
{
    remoteip_config_t *config = ap_get_module_config(cmd->server->module_config,
                                                     &remoteip_module);
    config->header_name = arg;
    return NULL;
}