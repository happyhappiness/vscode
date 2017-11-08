static void *config_server_create(apr_pool_t *p, server_rec *s)
{
    rewrite_server_conf *a;

    a = (rewrite_server_conf *)apr_pcalloc(p, sizeof(rewrite_server_conf));

    a->state           = ENGINE_DISABLED;
    a->options         = OPTION_NONE;
#ifndef REWRITELOG_DISABLED
    a->rewritelogfile  = NULL;
    a->rewritelogfp    = NULL;
    a->rewriteloglevel = 0;
#endif
    a->rewritemaps     = apr_hash_make(p);
    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));
    a->server          = s;

    return (void *)a;
}