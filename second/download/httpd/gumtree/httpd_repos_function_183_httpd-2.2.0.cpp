static dav_error * dav_generic_remove_lock(dav_lockdb *lockdb,
                                           const dav_resource *resource,
                                           const dav_locktoken *locktoken)
{
    dav_error *err;
    dav_lock_discovery *dh = NULL;
    dav_lock_indirect *ih = NULL;
    apr_datum_t key;

    key = dav_generic_build_key(lockdb->info->pool, resource);

    if (locktoken != NULL) {
        dav_lock_discovery *dp;
        dav_lock_discovery *dprev = NULL;
        dav_lock_indirect *ip;
        dav_lock_indirect *iprev = NULL;

        if ((err = dav_generic_load_lock_record(lockdb, key, DAV_CREATE_LIST,
                                           &dh, &ih)) != NULL) {
            /* ### maybe add a higher-level description */
            return err;
        }

        for (dp = dh; dp != NULL; dp = dp->next) {
            if (dav_compare_locktoken(locktoken, dp->locktoken) == 0) {
                if (dprev)
                    dprev->next = dp->next;
                else
                    dh = dh->next;
            }
            dprev = dp;
        }

        for (ip = ih; ip != NULL; ip = ip->next) {
            if (dav_compare_locktoken(locktoken, ip->locktoken) == 0) {
                if (iprev)
                    iprev->next = ip->next;
                else
                    ih = ih->next;
            }
            iprev = ip;
        }

    }

    /* save the modified locks, or remove all locks (dh=ih=NULL). */
    if ((err = dav_generic_save_lock_record(lockdb, key, dh, ih)) != NULL) {
        /* ### maybe add a higher-level description */
        return err;
    }

    return NULL;
}