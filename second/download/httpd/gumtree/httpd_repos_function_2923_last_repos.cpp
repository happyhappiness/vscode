static void *h2_config_merge(apr_pool_t *pool, void *basev, void *addv)
{
    h2_config *base = (h2_config *)basev;
    h2_config *add = (h2_config *)addv;
    h2_config *n = (h2_config *)apr_pcalloc(pool, sizeof(h2_config));
    char *name = apr_pstrcat(pool, "merged[", add->name, ", ", base->name, "]", NULL);
    n->name = name;

    n->h2_max_streams       = H2_CONFIG_GET(add, base, h2_max_streams);
    n->h2_window_size       = H2_CONFIG_GET(add, base, h2_window_size);
    n->min_workers          = H2_CONFIG_GET(add, base, min_workers);
    n->max_workers          = H2_CONFIG_GET(add, base, max_workers);
    n->max_worker_idle_secs = H2_CONFIG_GET(add, base, max_worker_idle_secs);
    n->stream_max_mem_size  = H2_CONFIG_GET(add, base, stream_max_mem_size);
    n->alt_svcs             = add->alt_svcs? add->alt_svcs : base->alt_svcs;
    n->alt_svc_max_age      = H2_CONFIG_GET(add, base, alt_svc_max_age);
    n->serialize_headers    = H2_CONFIG_GET(add, base, serialize_headers);
    n->h2_direct            = H2_CONFIG_GET(add, base, h2_direct);
    n->modern_tls_only      = H2_CONFIG_GET(add, base, modern_tls_only);
    n->h2_upgrade           = H2_CONFIG_GET(add, base, h2_upgrade);
    n->tls_warmup_size      = H2_CONFIG_GET(add, base, tls_warmup_size);
    n->tls_cooldown_secs    = H2_CONFIG_GET(add, base, tls_cooldown_secs);
    n->h2_push              = H2_CONFIG_GET(add, base, h2_push);
    if (add->priorities && base->priorities) {
        n->priorities       = apr_hash_overlay(pool, add->priorities, base->priorities);
    }
    else {
        n->priorities       = add->priorities? add->priorities : base->priorities;
    }
    n->push_diary_size      = H2_CONFIG_GET(add, base, push_diary_size);
    n->copy_files           = H2_CONFIG_GET(add, base, copy_files);
    if (add->push_list && base->push_list) {
        n->push_list        = apr_array_append(pool, base->push_list, add->push_list);
    }
    else {
        n->push_list        = add->push_list? add->push_list : base->push_list;
    }
    n->early_hints          = H2_CONFIG_GET(add, base, early_hints);
    return n;
}