int dav_unlock(request_rec *r, const dav_resource *resource,
               const dav_locktoken *locktoken)
{
    int result;
    dav_lockdb *lockdb;
    const dav_resource *lock_resource = resource;
    const dav_hooks_locks *hooks = DAV_GET_HOOKS_LOCKS(r);
    const dav_hooks_repository *repos_hooks = resource->hooks;
    dav_walker_ctx ctx = { { 0 } };
    dav_response *multi_status;
    dav_error *err;

    /* If no locks provider, then there is nothing to unlock. */
    if (hooks == NULL) {
        return OK;
    }

    /* 2518 requires the entire lock to be removed if resource/locktoken
     * point to an indirect lock.  We need resource of the _direct_
     * lock in order to walk down the tree and remove the locks.  So,
     * If locktoken != null_locktoken, 
     *    Walk up the resource hierarchy until we see a direct lock.
     *    Or, we could get the direct lock's db/key, pick out the URL
     *    and do a subrequest.  I think walking up is faster and will work
     *    all the time.
     * Else
     *    Just start removing all locks at and below resource.
     */

    if ((err = (*hooks->open_lockdb)(r, 0, 1, &lockdb)) != NULL) {
        /* ### return err! maybe add a higher-level desc */
        /* ### map result to something nice; log an error */
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (locktoken != NULL
        && (err = dav_get_direct_resource(r->pool, lockdb,
                                          locktoken, resource,
                                          &lock_resource)) != NULL) {
        /* ### add a higher-level desc? */
        /* ### should return err! */
        return err->status;
    }

    /* At this point, lock_resource/locktoken refers to a direct lock (key), ie
     * the root of a depth > 0 lock, or locktoken is null.
     */
    ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_LOCKNULL;
    ctx.w.func = dav_unlock_walker;
    ctx.w.walk_ctx = &ctx;
    ctx.w.pool = r->pool;
    ctx.w.root = lock_resource;
    ctx.w.lockdb = lockdb;

    ctx.r = r;
    ctx.locktoken = locktoken;

    err = (*repos_hooks->walk)(&ctx.w, DAV_INFINITY, &multi_status);

    /* ### fix this! */
    /* ### do something with multi_status */
    result = err == NULL ? OK : err->status;

    (*hooks->close_lockdb)(lockdb);

    return result;
}