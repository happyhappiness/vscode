void *h2_config_merge(apr_pool_t *pool, void *basev, void *addv)
{
    h2_config *base = (h2_config *)basev;
    h2_config *add = (h2_config *)addv;
    h2_config *n = (h2_config *)apr_pcalloc(pool, sizeof(h2_config));

    char *name = apr_pcalloc(pool, 20 + strlen(add->name) + strlen(base->name));
    strcpy(name, "merged[");
    strcat(name, add->name);
    strcat(name, ", ");
    strcat(name, base->name);
    strcat(name, "]");
    n->name = name;

    n->h2_max_streams = H2_CONFIG_GET(add, base, h2_max_streams);
    n->h2_window_size = H2_CONFIG_GET(add, base, h2_window_size);
    n->min_workers    = H2_CONFIG_GET(add, base, min_workers);
    n->max_workers    = H2_CONFIG_GET(add, base, max_workers);
    n->max_worker_idle_secs = H2_CONFIG_GET(add, base, max_worker_idle_secs);
    n->stream_max_mem_size = H2_CONFIG_GET(add, base, stream_max_mem_size);
    n->alt_svcs = add->alt_svcs? add->alt_svcs : base->alt_svcs;
    n->alt_svc_max_age = H2_CONFIG_GET(add, base, alt_svc_max_age);
    n->serialize_headers = H2_CONFIG_GET(add, base, serialize_headers);
    n->h2_direct      = H2_CONFIG_GET(add, base, h2_direct);
    n->session_extra_files = H2_CONFIG_GET(add, base, session_extra_files);
    
    return n;
}