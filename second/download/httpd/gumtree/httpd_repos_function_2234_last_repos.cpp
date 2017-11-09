static void *lb_hb_merge_config(apr_pool_t *p, void *basev, void *overridesv)
{
    lb_hb_ctx_t *ps = apr_pcalloc(p, sizeof(lb_hb_ctx_t));
    lb_hb_ctx_t *base = (lb_hb_ctx_t *) basev;
    lb_hb_ctx_t *overrides = (lb_hb_ctx_t *) overridesv;

    if (overrides->path) {
        ps->path = apr_pstrdup(p, overrides->path);
    }
    else {
        ps->path = apr_pstrdup(p, base->path);
    }

    return ps;
}