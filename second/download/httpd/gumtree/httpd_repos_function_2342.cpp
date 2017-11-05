static void *privileges_merge_cfg(apr_pool_t *pool, void *BASE, void *ADD)
{
    /* inherit the mode if it's not set; the rest won't be inherited */
    priv_cfg *base = BASE;
    priv_cfg *add = ADD;
    priv_cfg *ret = apr_pmemdup(pool, add, sizeof(priv_cfg));
    ret->mode = (add->mode == PRIV_UNSET) ? base->mode : add->mode;
    return ret;
}