static dav_error * dav_fs_append_locks(dav_lockdb *lockdb,
                                       const dav_resource *resource,
                                       int make_indirect,
                                       const dav_lock *lock)
{
    apr_pool_t *p = lockdb->info->pool;
    dav_error *err;
    dav_lock_indirect *ip;
    dav_lock_discovery *dp;
    apr_datum_t key;

    key = dav_fs_build_key(lockdb->info->pool, resource);
    if ((err = dav_fs_load_lock_record(lockdb, key, 0, &dp, &ip)) != NULL) {
        /* ### maybe add in a higher-level description */
        return err;
    }

    /*
    ** ### when we store the lock more directly, we need to update
    ** ### lock->rectype and lock->is_locknull
    */

    if (make_indirect) {
        for (; lock != NULL; lock = lock->next) {

            /* ### this works for any <lock> rectype */
            dav_lock_indirect *newi = apr_pcalloc(p, sizeof(*newi));

            /* ### shut off the const warning for now */
            newi->locktoken = (dav_locktoken *)lock->locktoken;
            newi->timeout   = lock->timeout;
            newi->key       = lock->info->key;
            newi->next      = ip;
            ip              = newi;
        }
    }
    else {
        for (; lock != NULL; lock = lock->next) {
            /* create and link in the right kind of lock */

            if (lock->rectype == DAV_LOCKREC_DIRECT) {
                dav_lock_discovery *newd = apr_pcalloc(p, sizeof(*newd));

                newd->f.scope = lock->scope;
                newd->f.type = lock->type;
                newd->f.depth = lock->depth;
                newd->f.timeout = lock->timeout;
                /* ### shut off the const warning for now */
                newd->locktoken = (dav_locktoken *)lock->locktoken;
                newd->owner = lock->owner;
                newd->auth_user = lock->auth_user;
                newd->next = dp;
                dp = newd;
            }
            else {
                /* DAV_LOCKREC_INDIRECT(_PARTIAL) */

                dav_lock_indirect *newi = apr_pcalloc(p, sizeof(*newi));

                /* ### shut off the const warning for now */
                newi->locktoken = (dav_locktoken *)lock->locktoken;
                newi->key       = lock->info->key;
                newi->next      = ip;
                ip              = newi;
            }
        }
    }

    if ((err = dav_fs_save_lock_record(lockdb, key, dp, ip)) != NULL) {
        /* ### maybe add a higher-level description */
        return err;
    }

    /* we have a special list for recording locknull resources */
    /* ### ack! this can add two copies to the locknull list */
    if (!resource->exists
        && (err = dav_fs_add_locknull_state(lockdb, resource)) != NULL) {
        /* ### maybe add a higher-level description */
        return err;
    }

    return NULL;
}