static int privileges_postconf(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp, server_rec *s)
{
    priv_cfg *cfg;
    server_rec *sp;

    /* if we have dtrace enabled, merge it into everything */
    if (dtrace_enabled) {
        for (sp = s; sp != NULL; sp = sp->next) {
            cfg = ap_get_module_config(sp->module_config, &privileges_module);
            CR_CHECK(priv_addset(cfg->priv, PRIV_DTRACE_KERNEL));
            CR_CHECK(priv_addset(cfg->priv, PRIV_DTRACE_PROC));
            CR_CHECK(priv_addset(cfg->priv, PRIV_DTRACE_USER));
            CR_CHECK(priv_addset(cfg->child_priv, PRIV_DTRACE_KERNEL));
            CR_CHECK(priv_addset(cfg->child_priv, PRIV_DTRACE_PROC));
            CR_CHECK(priv_addset(cfg->child_priv, PRIV_DTRACE_USER));
        }
        CR_CHECK(priv_addset(priv_default, PRIV_DTRACE_KERNEL));
        CR_CHECK(priv_addset(priv_default, PRIV_DTRACE_PROC));
        CR_CHECK(priv_addset(priv_default, PRIV_DTRACE_USER));
    }

    /* set up priv_setid for per-request use */
    priv_setid = priv_allocset();
    apr_pool_cleanup_register(pconf, NULL, privileges_term,
                              apr_pool_cleanup_null);
    priv_emptyset(priv_setid);
    if (priv_addset(priv_setid, PRIV_PROC_SETID) == -1) {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, errno, ptemp,
                      "priv_addset");
        return !OK;
    }
    return OK;
}