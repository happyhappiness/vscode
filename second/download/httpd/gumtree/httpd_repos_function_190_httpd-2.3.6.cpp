static dav_error * dav_generic_get_locks(dav_lockdb *lockdb,
                                         const dav_resource *resource,
                                         int calltype,
                                         dav_lock **locks)
{
    apr_pool_t *p = lockdb->info->pool;
    apr_datum_t key;
    dav_error *err;
    dav_lock *lock = NULL;
    dav_lock *newlock;
    dav_lock_discovery *dp;
    dav_lock_indirect *ip;

#if DAV_DEBUG
    if (calltype == DAV_GETLOCKS_COMPLETE) {
        return dav_new_error(lockdb->info->pool,
                             HTTP_INTERNAL_SERVER_ERROR, 0, 0,
                             "INTERNAL DESIGN ERROR: DAV_GETLOCKS_COMPLETE "
                             "is not yet supported");
    }
#endif

    key = dav_generic_build_key(p, resource);
    if ((err = dav_generic_load_lock_record(lockdb, key, DAV_CREATE_LIST,
                                            &dp, &ip)) != NULL) {
        /* ### push a higher-level desc? */
        return err;
    }

    /* copy all direct locks to the result list */
    for (; dp != NULL; dp = dp->next) {
        newlock = dav_generic_alloc_lock(lockdb, key, dp->locktoken);
        newlock->is_locknull = !resource->exists;
        newlock->scope = dp->f.scope;
        newlock->type = dp->f.type;
        newlock->depth = dp->f.depth;
        newlock->timeout = dp->f.timeout;
        newlock->owner = dp->owner;
        newlock->auth_user = dp->auth_user;

        /* hook into the result list */
        newlock->next = lock;
        lock = newlock;
    }

    /* copy all the indirect locks to the result list. resolve as needed. */
    for (; ip != NULL; ip = ip->next) {
        newlock = dav_generic_alloc_lock(lockdb, ip->key, ip->locktoken);
        newlock->is_locknull = !resource->exists;

        if (calltype == DAV_GETLOCKS_RESOLVED) {
            err = dav_generic_resolve(lockdb, ip, &dp, NULL, NULL);
            if (err != NULL) {
                /* ### push a higher-level desc? */
                return err;
            }

            newlock->scope = dp->f.scope;
            newlock->type = dp->f.type;
            newlock->depth = dp->f.depth;
            newlock->timeout = dp->f.timeout;
            newlock->owner = dp->owner;
            newlock->auth_user = dp->auth_user;
        }
        else {
            /* DAV_GETLOCKS_PARTIAL */
            newlock->rectype = DAV_LOCKREC_INDIRECT_PARTIAL;
        }

        /* hook into the result list */
        newlock->next = lock;
        lock = newlock;
    }

    *locks = lock;
    return NULL;
}