static const char *echo_on(cmd_parms *cmd, void *dummy, int arg)
{
    EchoConfig *pConfig = ap_get_module_config(cmd->server->module_config,
                                               &echo_module);
    pConfig->bEnabled = arg;

    return NULL;
}