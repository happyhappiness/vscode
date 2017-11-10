static const char *set_forensic_log(cmd_parms *cmd, void *dummy, const char *fn)
{
    fcfg *cfg = ap_get_module_config(cmd->server->module_config,
                                     &log_forensic_module);

    cfg->logname = fn;
    return NULL;
}