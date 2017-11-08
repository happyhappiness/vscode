static void *config_server_merge(apr_pool_t *p, void *basev, void *overridesv)
{
    rewrite_server_conf *a, *base, *overrides;

    a         = (rewrite_server_conf *)apr_pcalloc(p, sizeof(rewrite_server_conf));
    base      = (rewrite_server_conf *)basev;
    overrides = (rewrite_server_conf *)overridesv;

    a->state   = overrides->state;
    a->options = overrides->options;
    a->server  = overrides->server;

    if (a->options & OPTION_INHERIT) {
        /*
         *  local directives override
         *  and anything else is inherited
         */
        a->rewriteloglevel = overrides->rewriteloglevel != 0 
                             ? overrides->rewriteloglevel
                             : base->rewriteloglevel;
        a->rewritelogfile  = overrides->rewritelogfile != NULL 
                             ? overrides->rewritelogfile
                             : base->rewritelogfile;
        a->rewritelogfp    = overrides->rewritelogfp != NULL 
                             ? overrides->rewritelogfp 
                             : base->rewritelogfp;
        a->rewritemaps     = apr_array_append(p, overrides->rewritemaps,
                                              base->rewritemaps);
        a->rewriteconds    = apr_array_append(p, overrides->rewriteconds,
                                              base->rewriteconds);
        a->rewriterules    = apr_array_append(p, overrides->rewriterules,
                                              base->rewriterules);
    }
    else {
        /*
         *  local directives override
         *  and anything else gets defaults
         */
        a->rewriteloglevel = overrides->rewriteloglevel;
        a->rewritelogfile  = overrides->rewritelogfile;
        a->rewritelogfp    = overrides->rewritelogfp;
        a->rewritemaps     = overrides->rewritemaps;
        a->rewriteconds    = overrides->rewriteconds;
        a->rewriterules    = overrides->rewriterules;
    }

    return (void *)a;
}