static const char *dbd_param_flag(cmd_parms *cmd, void *cfg, int flag)
{
    svr_cfg *svr = (svr_cfg*) ap_get_module_config
        (cmd->server->module_config, &dbd_module);

    switch ((long) cmd->info) {
    case cmd_persist:
        svr->persist = flag;
        break;
    }
    return NULL;
}