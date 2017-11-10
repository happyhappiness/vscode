static const char *CaseFilterEnable(cmd_parms *cmd, void *dummy, int arg)
    {
    CaseFilterConfig *pConfig=ap_get_module_config(cmd->server->module_config,
                                                   &case_filter_module);
    pConfig->bEnabled=arg;

    return NULL;
    }