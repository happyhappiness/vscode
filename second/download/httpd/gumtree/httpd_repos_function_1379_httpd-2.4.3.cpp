static void *config_server_merge(apr_pool_t *p, void *basev, void *overridesv)
{
    rewrite_server_conf *a, *base, *overrides;

    a         = (rewrite_server_conf *)apr_pcalloc(p,
                                                   sizeof(rewrite_server_conf));
    base      = (rewrite_server_conf *)basev;
    overrides = (rewrite_server_conf *)overridesv;

    a->state = (overrides->state_set == 0) ? base->state : overrides->state;
    a->state_set = overrides->state_set || base->state_set;
    a->options = (overrides->options_set == 0) ? base->options : overrides->options;
    a->options_set = overrides->options_set || base->options_set;

    a->server  = overrides->server;

    if (a->options & OPTION_INHERIT) {
        /*
         *  local directives override
         *  and anything else is inherited
         */
        a->rewritemaps     = apr_hash_overlay(p, overrides->rewritemaps,
                                              base->rewritemaps);
        a->rewriteconds    = apr_array_append(p, overrides->rewriteconds,
                                              base->rewriteconds);
        a->rewriterules    = apr_array_append(p, overrides->rewriterules,
                                              base->rewriterules);
    }
    else if (a->options & OPTION_INHERIT_BEFORE) {
        /*
         *  local directives override
         *  and anything else is inherited (preserving order)
         */
        a->rewritemaps     = apr_hash_overlay(p, base->rewritemaps,
                                              overrides->rewritemaps);
        a->rewriteconds    = apr_array_append(p, base->rewriteconds,
                                              overrides->rewriteconds);
        a->rewriterules    = apr_array_append(p, base->rewriterules,
                                              overrides->rewriterules);
    }
    else {
        /*
         *  local directives override
         *  and anything else gets defaults
         */
        a->rewritemaps     = overrides->rewritemaps;
        a->rewriteconds    = overrides->rewriteconds;
        a->rewriterules    = overrides->rewriterules;
    }

    return (void *)a;
}