#ifndef NO_PROTOCOL
    int ranges = 1;
    mod_filter_ctx *ctx = apr_pcalloc(r->pool, sizeof(mod_filter_ctx));
    ap_set_module_config(r->request_config, &filter_module, ctx);
#endif

    /** IG: Now that we've merged to the final config, go one last time
     *  through the chain, and prune out the NULL filters */

    for (p = cfg->chain; p; p = p->next) {
        if (p->fname == NULL) 
            cfg->chain = p->next;
    }

    for (p = cfg->chain; p; p = p->next) {
        filter = apr_hash_get(cfg->live_filters, p->fname, APR_HASH_KEY_STRING);
        if (filter == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Unknown filter %s not added", p->fname);
            continue;
