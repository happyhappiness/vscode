static dav_error * dav_lock_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err;

    /* We don't want to set indirects on the target */
    if ((*wres->resource->hooks->is_same_resource)(wres->resource,
                                                   ctx->w.root))
        return NULL;

    if ((err = (*ctx->w.lockdb->hooks->append_locks)(ctx->w.lockdb,
                                                     wres->resource, 1,
                                                     ctx->lock)) != NULL) {
        if (ap_is_HTTP_SERVER_ERROR(err->status)) {
            /* ### add a higher-level description? */
            return err;
        }

        /* add to the multistatus response */
        dav_add_response(wres, err->status, NULL);

        /*
        ** ### actually, this is probably wrong: we want to fail the whole
        ** ### LOCK process if something goes bad. maybe the caller should
        ** ### do a dav_unlock() (e.g. a rollback) if any errors occurred.
        */
    }

    return NULL;
}