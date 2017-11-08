static void *log_debug_merge_dconf(apr_pool_t *p, void *parent_conf, void *new_conf)
{
    log_debug_dirconf *merged = apr_pcalloc(p, sizeof(log_debug_dirconf));
    const log_debug_dirconf *parent = parent_conf;
    const log_debug_dirconf *new = new_conf;

    if (parent->entries == NULL)
        merged->entries = new->entries;
    else if (new->entries == NULL)
        merged->entries = parent->entries;
    else
        /* apr_array_append actually creates a new array */
        merged->entries = apr_array_append(p, parent->entries, new->entries);

    return merged;
}