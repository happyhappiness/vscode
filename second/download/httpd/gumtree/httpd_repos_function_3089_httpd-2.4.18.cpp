static void *privileges_merge_dir_cfg(apr_pool_t *pool, void *BASE, void *ADD)
{
    priv_dir_cfg *base = BASE;
    priv_dir_cfg *add = ADD;
    priv_dir_cfg *ret = apr_palloc(pool, sizeof(priv_dir_cfg));
    ret->mode = (add->mode == PRIV_UNSET) ? base->mode : add->mode;
    return ret;
}