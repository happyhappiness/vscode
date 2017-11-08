static dav_error * dav_generic_has_locks(dav_lockdb *lockdb,
                                         const dav_resource *resource,
                                         int *locks_present)
{
    dav_error *err;
    apr_datum_t key;

    *locks_present = 0;

    if ((err = dav_generic_really_open_lockdb(lockdb)) != NULL) {
        /* ### insert a higher-level error description */
        return err;
    }

    /*
     * If we opened readonly and the db wasn't there, then there are no
     * locks for this resource. Just exit.
     */
    if (lockdb->info->db == NULL)
        return NULL;

    key = dav_generic_build_key(lockdb->info->pool, resource);

    *locks_present = apr_dbm_exists(lockdb->info->db, key);

    return NULL;
}