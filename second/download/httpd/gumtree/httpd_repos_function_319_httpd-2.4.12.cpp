static dav_error * dav_inherit_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;

    if (ctx->skip_root
        && (*wres->resource->hooks->is_same_resource)(wres->resource,
                                                      ctx->w.root)) {
        return NULL;
    }

    /* ### maybe add a higher-level desc */
    return (*ctx->w.lockdb->hooks->append_locks)(ctx->w.lockdb,
                                                 wres->resource, 1,
                                                 ctx->lock);
}