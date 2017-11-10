static void *merge_headers_config(apr_pool_t *p, void *basev, void *overridesv)
{
    headers_conf *newconf = apr_pcalloc(p, sizeof(*newconf));
    headers_conf *base = basev;
    headers_conf *overrides = overridesv;

    newconf->fixup_in = apr_array_append(p, base->fixup_in,
                                         overrides->fixup_in);
    newconf->fixup_out = apr_array_append(p, base->fixup_out,
                                          overrides->fixup_out);
    newconf->fixup_err = apr_array_append(p, base->fixup_err,
                                          overrides->fixup_err);

    return newconf;
}