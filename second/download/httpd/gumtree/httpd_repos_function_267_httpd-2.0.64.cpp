static dav_error * dav_inherit_locks(request_rec *r, dav_lockdb *lockdb,
                                     const dav_resource *resource,
                                     int use_parent)
{
    dav_error *err;
    const dav_resource *which_resource;
    dav_lock *locks;
    dav_lock *scan;
    dav_lock *prev;
    dav_walker_ctx ctx = { { 0 } };
    const dav_hooks_repository *repos_hooks = resource->hooks;
    dav_response *multi_status;

    if (use_parent) {
        dav_resource *parent;
        if ((err = (*repos_hooks->get_parent_resource)(resource,
                                                       &parent)) != NULL) {
            /* ### add a higher-level desc? */
            return err;
        }
        if (parent == NULL) {
            /* ### map result to something nice; log an error */
            return dav_new_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "Could not fetch parent resource. Unable to "
                                 "inherit locks from the parent and apply "
                                 "them to this resource.");
        }
        which_resource = parent;
    }
    else {
        which_resource = resource;
    }

    if ((err = (*lockdb->hooks->get_locks)(lockdb, which_resource,
                                           DAV_GETLOCKS_PARTIAL,
                                           &locks)) != NULL) {
        /* ### maybe add a higher-level desc */
        return err;
    }

    if (locks == NULL) {
        /* No locks to propagate, just return */
        return NULL;
    }

    /*
    ** (1) Copy all indirect locks from our parent;
    ** (2) Create indirect locks for the depth infinity, direct locks
    **     in our parent.
    **
    ** The append_locks call in the walker callback will do the indirect
    ** conversion, but we need to remove any direct locks that are NOT
    ** depth "infinity".
    */
    for (scan = locks, prev = NULL;
         scan != NULL;
         prev = scan, scan = scan->next) {

        if (scan->rectype == DAV_LOCKREC_DIRECT
            && scan->depth != DAV_INFINITY) {

            if (prev == NULL)
                locks = scan->next;
            else
                prev->next = scan->next;
        }
    }

    /* <locks> has all our new locks.  Walk down and propagate them. */

    ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_LOCKNULL;
    ctx.w.func = dav_inherit_walker;
    ctx.w.walk_ctx = &ctx;
    ctx.w.pool = r->pool;
    ctx.w.root = resource;
    ctx.w.lockdb = lockdb;

    ctx.r = r;
    ctx.lock = locks;
    ctx.skip_root = !use_parent;

    /* ### do something with multi_status */
    return (*repos_hooks->walk)(&ctx.w, DAV_INFINITY, &multi_status);
}