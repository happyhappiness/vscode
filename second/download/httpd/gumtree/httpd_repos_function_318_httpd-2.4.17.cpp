static dav_error * dav_get_direct_resource(apr_pool_t *p,
                                           dav_lockdb *lockdb,
                                           const dav_locktoken *locktoken,
                                           const dav_resource *resource,
                                           const dav_resource **direct_resource)
{
    if (lockdb->hooks->lookup_resource != NULL) {
        return (*lockdb->hooks->lookup_resource)(lockdb, locktoken,
                                                 resource, direct_resource);
    }

    *direct_resource = NULL;

    /* Find the top of this lock-
     * If r->filename's direct   locks include locktoken, use r->filename.
     * If r->filename's indirect locks include locktoken, retry r->filename/..
     * Else fail.
     */
    while (resource != NULL) {
        dav_error *err;
        dav_lock *lock;
        dav_resource *parent;

        /*
        ** Find the lock specified by <locktoken> on <resource>. If it is
        ** an indirect lock, then partial results are okay. We're just
        ** trying to find the thing and know whether it is a direct or
        ** an indirect lock.
        */
        if ((err = (*lockdb->hooks->find_lock)(lockdb, resource, locktoken,
                                               1, &lock)) != NULL) {
            /* ### add a higher-level desc? */
            return err;
        }

        /* not found! that's an error. */
        if (lock == NULL) {
            return dav_new_error(p, HTTP_BAD_REQUEST, 0, 0,
                                 "The specified locktoken does not correspond "
                                 "to an existing lock on this resource.");
        }

        if (lock->rectype == DAV_LOCKREC_DIRECT) {
            /* we found the direct lock. return this resource. */

            *direct_resource = resource;
            return NULL;
        }

        /* the lock was indirect. move up a level in the URL namespace */
        if ((err = (*resource->hooks->get_parent_resource)(resource,
                                                           &parent)) != NULL) {
            /* ### add a higher-level desc? */
            return err;
        }
        resource = parent;
    }

    return dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, 0, 0,
                         "The lock database is corrupt. A direct lock could "
                         "not be found for the corresponding indirect lock "
                         "on this resource.");
}