static const char *dbd_param(cmd_parms *cmd, void *dconf, const char *val)
{
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
        switch (apr_dbd_get_driver(cmd->pool, cfg->name, &driver)) {
        case APR_ENOTIMPL:
            return apr_psprintf(cmd->pool, "DBD: No driver for %s", cfg->name);
        case APR_EDSOOPEN:
            return apr_psprintf(cmd->pool,
#ifdef NETWARE
                                "DBD: Can't load driver file dbd%s.nlm",
#else
                                "DBD: Can't load driver file apr_dbd_%s.so",
#endif
                                cfg->name);
        case APR_ESYMNOTFOUND:
            return apr_psprintf(cmd->pool,
                                "DBD: Failed to load driver apr_dbd_%s_driver",
                                cfg->name);
        }
        break;
    case cmd_params:
        cfg->params = val;
        break;
#if APR_HAS_THREADS
    case cmd_min:
        ISINT(val);
        cfg->nmin = atoi(val);
        cfg->set |= NMIN_SET;
        break;
    case cmd_keep:
        ISINT(val);
        cfg->nkeep = atoi(val);
        cfg->set |= NKEEP_SET;
        break;
    case cmd_max:
        ISINT(val);
        cfg->nmax = atoi(val);
        cfg->set |= NMAX_SET;
        break;
    case cmd_exp:
        ISINT(val);
        cfg->exptime = atoi(val);
        cfg->set |= EXPTIME_SET;
        break;
#endif
    }

    return NULL;
}