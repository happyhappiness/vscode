static void *merge_setenvif_config(apr_pool_t *p, void *basev, void *overridesv)
{
    sei_cfg_rec *a = apr_pcalloc(p, sizeof(sei_cfg_rec));
    sei_cfg_rec *base = basev, *overrides = overridesv;

    a->conditionals = apr_array_append(p, base->conditionals,
                                       overrides->conditionals);
    return a;
}