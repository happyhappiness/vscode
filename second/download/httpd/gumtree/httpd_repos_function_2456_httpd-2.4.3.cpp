static int privileges_drop_last(apr_pool_t *pool, server_rec *s)
{
    /* Our config stuff has set the privileges we need, so now
     * we just set them to those of the parent server_rec
     *
     * This has to happen after mod_unixd, 'cos mod_unixd needs
     * privileges we drop here.
     */
    priv_cfg *cfg = ap_get_module_config(s->module_config, &privileges_module);

    /* defaults - the default vhost */
    PDROP_CHECK(setppriv(PRIV_SET, PRIV_LIMIT, cfg->child_priv))
    PDROP_CHECK(setppriv(PRIV_SET, PRIV_INHERITABLE, cfg->child_priv))
    PDROP_CHECK(setppriv(PRIV_SET, PRIV_EFFECTIVE, cfg->priv))

    return OK;
}