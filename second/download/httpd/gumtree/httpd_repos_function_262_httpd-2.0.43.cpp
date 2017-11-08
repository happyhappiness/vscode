dav_error * dav_add_lock(request_rec *r, const dav_resource *resource,
			 dav_lockdb *lockdb, dav_lock *lock,
			 dav_response **response)
{
    dav_error *err;
    int depth = lock->depth;

    *response = NULL;

    /* Requested lock can be:
     *   Depth: 0   for null resource, existing resource, or existing collection
     *   Depth: Inf for existing collection
     */

    /*
    ** 2518 9.2 says to ignore depth if target is not a collection (it has
    **   no internal children); pretend the client gave the correct depth.
    */
    if (!resource->collection) {
	depth = 0;
    }

    /* In all cases, first add direct entry in lockdb */

    /*
    ** Append the new (direct) lock to the resource's existing locks.
    **
    ** Note: this also handles locknull resources
    */
    if ((err = (*lockdb->hooks->append_locks)(lockdb, resource, 0,
                                              lock)) != NULL) {
	/* ### maybe add a higher-level description */
	return err;
    }

    if (depth > 0) {
	/* Walk existing collection and set indirect locks */
        dav_walker_ctx ctx = { { 0 } };
        dav_response *multi_status;

	ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_AUTH;
	ctx.w.func = dav_lock_walker;
        ctx.w.walk_ctx = &ctx;
	ctx.w.pool = r->pool;
        ctx.w.root = resource;
	ctx.w.lockdb = lockdb;

	ctx.r = r;
	ctx.lock = lock;

	err = (*resource->hooks->walk)(&ctx.w, DAV_INFINITY, &multi_status);
	if (err != NULL) {
	    /* implies a 5xx status code occurred. screw the multistatus */
	    return err;
	}

	if (multi_status != NULL) {
	    /* manufacture a 207 error for the multistatus response */
	    *response = multi_status;
	    return dav_new_error(r->pool, HTTP_MULTI_STATUS, 0,
				 "Error(s) occurred on resources during the "
				 "addition of a depth lock.");
	}
    }

    return NULL;
}