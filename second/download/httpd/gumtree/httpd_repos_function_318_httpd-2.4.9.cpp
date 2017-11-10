static dav_error * dav_unlock_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err;

    /* Before removing the lock, do any auto-checkin required */
    if (wres->resource->working) {
        /* ### get rid of this typecast */
        if ((err = dav_auto_checkin(ctx->r, (dav_resource *) wres->resource,
                                    0 /*undo*/, 1 /*unlock*/, NULL))
            != NULL) {
            return err;
        }
    }

    if ((err = (*ctx->w.lockdb->hooks->remove_lock)(ctx->w.lockdb,
                                                    wres->resource,
                                                    ctx->locktoken)) != NULL) {
        /* ### should we stop or return a multistatus? looks like STOP */
        /* ### add a higher-level description? */
        return err;
    }

    return NULL;
}