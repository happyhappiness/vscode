static dav_error * dav_fs_find_lock(dav_lockdb *lockdb,
                                    const dav_resource *resource,
                                    const dav_locktoken *locktoken,
                                    int partial_ok,
                                    dav_lock **lock)
{
    dav_error *err;
    apr_datum_t key;
    dav_lock_discovery *dp;
    dav_lock_indirect *ip;

    *lock = NULL;

    key = dav_fs_build_key(lockdb->info->pool, resource);
    if ((err = dav_fs_load_lock_record(lockdb, key, DAV_CREATE_LIST,
                                       &dp, &ip)) != NULL) {
        /* ### push a higher-level desc? */
        return err;
    }

    for (; dp != NULL; dp = dp->next) {
        if (!dav_compare_locktoken(locktoken, dp->locktoken)) {
            *lock = dav_fs_alloc_lock(lockdb, key, locktoken);
            (*lock)->is_locknull = !resource->exists;
            (*lock)->scope = dp->f.scope;
            (*lock)->type = dp->f.type;
            (*lock)->depth = dp->f.depth;
            (*lock)->timeout = dp->f.timeout;
            (*lock)->owner = dp->owner;
            (*lock)->auth_user = dp->auth_user;
            return NULL;
        }
    }

    for (; ip != NULL; ip = ip->next) {
        if (!dav_compare_locktoken(locktoken, ip->locktoken)) {
            *lock = dav_fs_alloc_lock(lockdb, ip->key, locktoken);
            (*lock)->is_locknull = !resource->exists;

            /* ### nobody uses the resolving right now! */
            if (partial_ok) {
                (*lock)->rectype = DAV_LOCKREC_INDIRECT_PARTIAL;
            }
            else {
                (*lock)->rectype = DAV_LOCKREC_INDIRECT;
                if ((err = dav_fs_resolve(lockdb, ip, &dp,
                                          NULL, NULL)) != NULL) {
                    /* ### push a higher-level desc? */
                    return err;
                }
                (*lock)->scope = dp->f.scope;
                (*lock)->type = dp->f.type;
                (*lock)->depth = dp->f.depth;
                (*lock)->timeout = dp->f.timeout;
                (*lock)->owner = dp->owner;
                (*lock)->auth_user = dp->auth_user;
            }
            return NULL;
        }
    }

    return NULL;
}