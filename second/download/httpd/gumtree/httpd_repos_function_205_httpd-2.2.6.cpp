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

    {
        dav_lock_discovery *ld;
        dav_lock_indirect  *id;
        apr_datum_t key;

        /*
        ** Fetch the lock(s) that made the resource lock-null. Remove
        ** them under the filename key. Obtain the new inode key, and
        ** save the same lock information under it.
        */
        key = dav_fs_build_fname_key(p, pathname);
        if ((err = dav_fs_load_lock_record(lockdb, key, DAV_CREATE_LIST,
                                           &ld, &id)) != NULL) {
            /* ### insert a higher-level error description */
            return err;
        }

        if ((err = dav_fs_save_lock_record(lockdb, key, NULL, NULL)) != NULL) {
            /* ### insert a higher-level error description */
            return err;
        }

        key = dav_fs_build_key(p, resource);
        if ((err = dav_fs_save_lock_record(lockdb, key, ld, id)) != NULL) {
            /* ### insert a higher-level error description */
            return err;
        }
    }

    return NULL;
}