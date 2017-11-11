static apr_status_t priv_cfg_cleanup(void *CFG)
{
    priv_cfg *cfg = CFG;
    priv_freeset(cfg->priv);
    priv_freeset(cfg->child_priv);
    return APR_SUCCESS;
}