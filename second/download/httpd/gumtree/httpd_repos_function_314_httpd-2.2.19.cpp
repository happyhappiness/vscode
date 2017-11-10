static dav_error * dav_can_auto_checkout(
    request_rec *r,
    dav_resource *resource,
    dav_auto_version auto_version,
    dav_lockdb **lockdb,
    int *auto_checkout)
{
    dav_error *err;
    dav_lock *lock_list;

    *auto_checkout = 0;

    if (auto_version == DAV_AUTO_VERSION_ALWAYS) {
        *auto_checkout = 1;
    }
    else if (auto_version == DAV_AUTO_VERSION_LOCKED) {
        if (*lockdb == NULL) {
            const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);

            if (locks_hooks == NULL) {
                return dav_new_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     "Auto-checkout is only enabled for locked resources, "
                                     "but there is no lock provider.");
            }

            if ((err = (*locks_hooks->open_lockdb)(r, 0, 0, lockdb)) != NULL) {
                return dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                      "Cannot open lock database to determine "
                                      "auto-versioning behavior.",
                                      err);
            }
        }

        if ((err = dav_lock_query(*lockdb, resource, &lock_list)) != NULL) {
            return dav_push_error(r->pool,
                                  HTTP_INTERNAL_SERVER_ERROR, 0,
                                  "The locks could not be queried for "
                                  "determining auto-versioning behavior.",
                                  err);
        }

        if (lock_list != NULL)
            *auto_checkout = 1;
    }

    return NULL;
}