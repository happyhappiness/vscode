static void *dav_lock_merge_dir_config(apr_pool_t *p,
                                       void *base, void *overrides)
{
    dav_lock_dir_conf *parent = base;
    dav_lock_dir_conf *child = overrides;
    dav_lock_dir_conf *newconf;

    newconf = apr_pcalloc(p, sizeof(*newconf));

    newconf->lockdb_path =
        child->lockdb_path ? child->lockdb_path : parent->lockdb_path;

    return newconf;
}