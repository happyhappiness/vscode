static const char *dbd_param_int(cmd_parms *cmd, void *dconf, const char *val)
{
    svr_cfg *svr = ap_get_module_config(cmd->server->module_config,
                                        &dbd_module);
    dbd_cfg_t *cfg = svr->cfg;
    const char *p;

    for (p = val; *p; ++p) {
        if (!apr_isdigit(*p)) {
            return "Argument must be numeric!";
        }
    }

    switch ((long) cmd->info) {
    case cmd_min:
        cfg->nmin = atoi(val);
        cfg->set |= NMIN_SET;
        break;
    case cmd_keep:
        cfg->nkeep = atoi(val);
        cfg->set |= NKEEP_SET;
        break;
    case cmd_max:
        cfg->nmax = atoi(val);
        cfg->set |= NMAX_SET;
        break;
    case cmd_exp:
        cfg->exptime = atoi(val);
        cfg->set |= EXPTIME_SET;
        break;
    }

    return NULL;
}