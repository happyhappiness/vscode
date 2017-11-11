static void *config_perdir_merge(apr_pool_t *p, void *basev, void *overridesv)
{
    rewrite_perdir_conf *a, *base, *overrides;

    a         = (rewrite_perdir_conf *)apr_pcalloc(p,
                                                  sizeof(rewrite_perdir_conf));
    base      = (rewrite_perdir_conf *)basev;
    overrides = (rewrite_perdir_conf *)overridesv;

    a->state     = overrides->state;
    a->options   = overrides->options;
    a->directory = overrides->directory;
    a->baseurl   = overrides->baseurl;
    a->redirect_limit = overrides->redirect_limit
                          ? overrides->redirect_limit
                          : base->redirect_limit;

    if (a->options & OPTION_INHERIT) {
        a->rewriteconds = apr_array_append(p, overrides->rewriteconds,
                                           base->rewriteconds);
        a->rewriterules = apr_array_append(p, overrides->rewriterules,
                                           base->rewriterules);
    }
    else {
        a->rewriteconds = overrides->rewriteconds;
        a->rewriterules = overrides->rewriterules;
    }

    return (void *)a;
}