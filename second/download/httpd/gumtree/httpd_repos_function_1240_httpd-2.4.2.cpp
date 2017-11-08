static const char *dbd_param_flag(cmd_parms *cmd, void *dconf, int flag)
{
    svr_cfg *svr = ap_get_module_config(cmd->server->module_config,
                                        &dbd_module);

    switch ((long) cmd->info) {
    case cmd_persist:
        svr->cfg->persist = flag;
        break;
    }

    return NULL;
}