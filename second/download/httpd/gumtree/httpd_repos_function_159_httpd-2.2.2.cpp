static void *dav_lock_create_dir_config(apr_pool_t *p, char *dir)
{
    return apr_pcalloc(p, sizeof(dav_lock_dir_conf));
}