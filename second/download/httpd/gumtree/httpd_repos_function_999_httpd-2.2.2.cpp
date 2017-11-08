static const char *dbd_param(cmd_parms *cmd, void *cfg, const char *val)
{
    const char *p;
    const apr_dbd_driver_t *driver = NULL;
    svr_cfg *svr = (svr_cfg*) ap_get_module_config
        (cmd->server->module_config, &dbd_module);

    switch ((long) cmd->info) {
    case cmd_name:
        svr->name = val;
        /* loading the driver involves once-only dlloading that is
         * best done at server startup.  This also guarantees that
         * we won't return an error later.
         */
        switch (apr_dbd_get_driver(cmd->pool, svr->name, &driver)) {
        case APR_ENOTIMPL:
            return apr_psprintf(cmd->pool, "DBD: No driver for %s", svr->name);
        case APR_EDSOOPEN:
            return apr_psprintf(cmd->pool,
                                "DBD: Can't load driver file apr_dbd_%s.so",
                                svr->name);
        case APR_ESYMNOTFOUND:
            return apr_psprintf(cmd->pool,
                                "DBD: Failed to load driver apr_dbd_%s_driver",
                                svr->name);
        }
        break;
    case cmd_params:
        svr->params = val;
        break;
#if APR_HAS_THREADS
    case cmd_min:
        ISINT(val);
        svr->nmin = atoi(val);
        svr->set |= NMIN_SET;
        break;
    case cmd_keep:
        ISINT(val);
        svr->nkeep = atoi(val);
        svr->set |= NKEEP_SET;
        break;
    case cmd_max:
        ISINT(val);
        svr->nmax = atoi(val);
        svr->set |= NMAX_SET;
        break;
    case cmd_exp:
        ISINT(val);
        svr->exptime = atoi(val);
        svr->set |= EXPTIME_SET;
        break;
#endif
    }
    return NULL;
}