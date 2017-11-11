static dav_error * dav_fs_refresh_locks(dav_lockdb *lockdb,
                                        const dav_resource *resource,
                                        const dav_locktoken_list *ltl,
                                        time_t new_time,
                                        dav_lock **locks)
{
    dav_error *err;
    apr_datum_t key;
    dav_lock_discovery *dp;
    dav_lock_discovery *dp_scan;
    dav_lock_indirect *ip;
    int dirty = 0;
    dav_lock *newlock;

    *locks = NULL;

    key = dav_fs_build_key(lockdb->info->pool, resource);
    if ((err = dav_fs_load_lock_record(lockdb, key, DAV_CREATE_LIST,
                                       &dp, &ip)) != NULL) {
        /* ### maybe add in a higher-level description */
        return err;
    }

    /* ### we should be refreshing direct AND (resolved) indirect locks! */

    /* refresh all of the direct locks on this resource */
    for (dp_scan = dp; dp_scan != NULL; dp_scan = dp_scan->next) {
        if (dav_fs_do_refresh(dp_scan, ltl, new_time)) {
            /* the lock was refreshed. return the lock. */
            newlock = dav_fs_alloc_lock(lockdb, key, dp_scan->locktoken);
            newlock->is_locknull = !resource->exists;
            newlock->scope = dp_scan->f.scope;
            newlock->type = dp_scan->f.type;
            newlock->depth = dp_scan->f.depth;
            newlock->timeout = dp_scan->f.timeout;
            newlock->owner = dp_scan->owner;
            newlock->auth_user = dp_scan->auth_user;

            newlock->next = *locks;
            *locks = newlock;

            dirty = 1;
        }
    }

    /* if we refreshed any locks, then save them back. */
    if (dirty
        && (err = dav_fs_save_lock_record(lockdb, key, dp, ip)) != NULL) {
        /* ### maybe add in a higher-level description */
        return err;
    }

    /* for each indirect lock, find its direct lock and refresh it. */
    for (; ip != NULL; ip = ip->next) {
        dav_lock_discovery *ref_dp;
        dav_lock_indirect *ref_ip;

        if ((err = dav_fs_resolve(lockdb, ip, &dp_scan,
                                  &ref_dp, &ref_ip)) != NULL) {
            /* ### push a higher-level desc? */
            return err;
        }
        if (dav_fs_do_refresh(dp_scan, ltl, new_time)) {
            /* the lock was refreshed. return the lock. */
            newlock = dav_fs_alloc_lock(lockdb, ip->key, dp_scan->locktoken);
            newlock->is_locknull = !resource->exists;
            newlock->scope = dp_scan->f.scope;
            newlock->type = dp_scan->f.type;
            newlock->depth = dp_scan->f.depth;
            newlock->timeout = dp_scan->f.timeout;
            newlock->owner = dp_scan->owner;
            newlock->auth_user = dp_scan->auth_user;

            newlock->next = *locks;
            *locks = newlock;

            /* save the (resolved) direct lock back */
            if ((err = dav_fs_save_lock_record(lockdb, ip->key, ref_dp,
                                               ref_ip)) != NULL) {
                /* ### push a higher-level desc? */
                return err;
            }
        }
    }

    return NULL;
}