static const char *CaseFilterInEnable(cmd_parms *cmd, void *dummy, int arg)
{
    CaseFilterInConfig *pConfig
      = ap_get_module_config(cmd->server->module_config,
                             &case_filter_in_module);
    pConfig->bEnabled=arg;

    return NULL;
}