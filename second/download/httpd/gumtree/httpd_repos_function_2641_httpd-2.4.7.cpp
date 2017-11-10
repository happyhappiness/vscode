static void *privileges_create_cfg(apr_pool_t *pool, server_rec *s)
{
    priv_cfg *cfg = apr_palloc(pool, sizeof(priv_cfg));

    /* Start at basic privileges all round. */
    cfg->priv = priv_str_to_set("basic", ",", NULL);
    cfg->child_priv = priv_str_to_set("basic", ",", NULL);

    /* By default, run in secure vhost mode.
     * That means dropping basic privileges we don't usually need.
     */
    CR_CHECK(priv_delset(cfg->priv, PRIV_FILE_LINK_ANY));
    CR_CHECK(priv_delset(cfg->priv, PRIV_PROC_INFO));
    CR_CHECK(priv_delset(cfg->priv, PRIV_PROC_SESSION));

/* Hmmm, should CGI default to secure too ? */
/*
    CR_CHECK(priv_delset(cfg->child_priv, PRIV_FILE_LINK_ANY));
    CR_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_INFO));
    CR_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_SESSION));
    CR_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_FORK));
    CR_CHECK(priv_delset(cfg->child_priv, PRIV_PROC_EXEC));
*/

    /* we´ll use 0 for unset */
    cfg->uid = 0;
    cfg->gid = 0;
    cfg->mode = PRIV_UNSET;
    apr_pool_cleanup_register(pool, cfg, priv_cfg_cleanup,
                              apr_pool_cleanup_null);

    /* top-level default_priv wants the top-level cfg */
    if (priv_default == NULL) {
        priv_default = cfg->priv;
    }
    return cfg;
}