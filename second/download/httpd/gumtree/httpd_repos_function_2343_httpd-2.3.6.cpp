static int privileges_drop_first(apr_pool_t *pool, server_rec *s)
{
    /* We need to set privileges before mod_unixd,
     * 'cos otherwise setuid will wipe our privilege to do so
     */
    priv_cfg *spcfg;
    server_rec *sp;
    priv_set_t *ppriv = priv_allocset();

    /* compute ppriv from the union of all the vhosts plus setid */
    priv_copyset(priv_setid, ppriv);
    for (sp = s; sp != NULL; sp=sp->next) {
        spcfg = ap_get_module_config(sp->module_config, &privileges_module);
        priv_union(spcfg->priv, ppriv);
    }
    PDROP_CHECK(setppriv(PRIV_SET, PRIV_PERMITTED, ppriv))
    PDROP_CHECK(setppriv(PRIV_SET, PRIV_EFFECTIVE, ppriv))
    priv_freeset(ppriv);

    return OK;
}