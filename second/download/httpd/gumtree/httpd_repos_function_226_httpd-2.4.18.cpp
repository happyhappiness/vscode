static dav_error * dav_fs_remove_locknull_state(
    dav_lockdb *lockdb,
    const dav_resource *resource)
{
    dav_buffer buf = { 0 };
    dav_error *err;
    apr_pool_t *p = lockdb->info->pool;
    const char *pathname = dav_fs_pathname(resource);

    if ((err = dav_fs_remove_locknull_member(p, pathname, &buf)) != NULL) {
        /* ### add a higher-level description? */
        return err;
    }

    return NULL;
}