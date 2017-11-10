static const char *dbd_param(cmd_parms *cmd, void *dconf, const char *val)
{
    apr_status_t rv;
    const apr_dbd_driver_t *driver = NULL;
    svr_cfg *svr = ap_get_module_config(cmd->server->module_config,
                                        &dbd_module);
    dbd_cfg_t *cfg = svr->cfg;

    switch ((long) cmd->info) {
    case cmd_name:
        cfg->name = val;
        /* loading the driver involves once-only dlloading that is
         * best done at server startup.  This also guarantees that
         * we won't return an error later.
         */
        rv = apr_dbd_get_driver(cmd->pool, cfg->name, &driver);
        if (APR_STATUS_IS_ENOTIMPL(rv)) {
            return apr_psprintf(cmd->pool, "DBD: No driver for %s", cfg->name);
        }
        else if (APR_STATUS_IS_EDSOOPEN(rv)) {
            return apr_psprintf(cmd->pool,
#ifdef NETWARE
                                "DBD: Can't load driver file dbd%s.nlm",
#else
                                "DBD: Can't load driver file apr_dbd_%s.so",
#endif
                                cfg->name);
        }
        else if (APR_STATUS_IS_ESYMNOTFOUND(rv)) {
            return apr_psprintf(cmd->pool,
                                "DBD: Failed to load driver apr_dbd_%s_driver",
                                cfg->name);
        }
        break;
    case cmd_params:
        cfg->params = val;
        break;
    }

    return NULL;
}