static dav_error * dav_generic_resolve(dav_lockdb *lockdb,
                                       dav_lock_indirect *indirect,
                                       dav_lock_discovery **direct,
                                       dav_lock_discovery **ref_dp,
                                       dav_lock_indirect **ref_ip)
{
    dav_error *err;
    dav_lock_discovery *dir;
    dav_lock_indirect *ind;

    if ((err = dav_generic_load_lock_record(lockdb, indirect->key,
                                       DAV_CREATE_LIST,
                                       &dir, &ind)) != NULL) {
        /* ### insert a higher-level description? */
        return err;
    }
    if (ref_dp != NULL) {
        *ref_dp = dir;
        *ref_ip = ind;
    }

    for (; dir != NULL; dir = dir->next) {
        if (!dav_compare_locktoken(indirect->locktoken, dir->locktoken)) {
            *direct = dir;
            return NULL;
        }
    }

    /* No match found (but we should have found one!) */

    /* ### use a different description and/or error ID? */
    return dav_new_error(lockdb->info->pool,
                         HTTP_INTERNAL_SERVER_ERROR,
                         DAV_ERR_LOCK_CORRUPT_DB,
                         "The lock database was found to be corrupt. "
                         "An indirect lock's direct lock could not "
                         "be found.");
}