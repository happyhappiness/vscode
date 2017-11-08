dav_error * dav_notify_created(request_rec *r,
			       dav_lockdb *lockdb,
			       const dav_resource *resource,
			       int resource_state,
			       int depth)
{
    dav_error *err;

    if (resource_state == DAV_RESOURCE_LOCK_NULL) {

	/*
	** The resource is no longer a locknull resource. This will remove
	** the special marker.
	**
	** Note that a locknull resource has already inherited all of the
	** locks from the parent. We do not need to call dav_inherit_locks.
	**
	** NOTE: some lock providers record locks for locknull resources using
	**       a different key than for regular resources. this will shift
	**       the lock information between the two key types.
	*/
	(void)(*lockdb->hooks->remove_locknull_state)(lockdb, resource);

	/*
	** There are resources under this one, which are new. We must
	** propagate the locks down to the new resources.
	*/
	if (depth > 0 &&
	    (err = dav_inherit_locks(r, lockdb, resource, 0)) != NULL) {
	    /* ### add a higher level desc? */
	    return err;
	}
    }
    else if (resource_state == DAV_RESOURCE_NULL) {

	/* ### should pass depth to dav_inherit_locks so that it can
	** ### optimize for the depth==0 case.
	*/

	/* this resource should inherit locks from its parent */
	if ((err = dav_inherit_locks(r, lockdb, resource, 1)) != NULL) {

	    err = dav_push_error(r->pool, err->status, 0,
				 "The resource was created successfully, but "
				 "there was a problem inheriting locks from "
				 "the parent resource.",
				 err);
	    return err;
	}
    }
    /* else the resource already exists and its locks are correct. */

    return NULL;
}