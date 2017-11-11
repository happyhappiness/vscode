static void *config_perdir_merge(apr_pool_t *p, void *basev, void *overridesv)
{
    rewrite_perdir_conf *a, *base, *overrides;

    a         = (rewrite_perdir_conf *)apr_pcalloc(p,
                                                  sizeof(rewrite_perdir_conf));
    base      = (rewrite_perdir_conf *)basev;
    overrides = (rewrite_perdir_conf *)overridesv;

    a->state = (overrides->state_set == 0) ? base->state : overrides->state;
    a->state_set = overrides->state_set || base->state_set;
    a->options = (overrides->options_set == 0) ? base->options : overrides->options;
    a->options_set = overrides->options_set || base->options_set;

    if (a->options & OPTION_MERGEBASE) { 
        a->baseurl = (overrides->baseurl_set == 0) ? base->baseurl : overrides->baseurl;
        a->baseurl_set = overrides->baseurl_set || base->baseurl_set;
    }
    else { 
        a->baseurl = overrides->baseurl;
    }

    a->directory  = overrides->directory;

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