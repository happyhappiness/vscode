static dav_error * dav_propfind_walker(dav_walk_resource *wres, int calltype)
{
    dav_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err;
    dav_propdb *propdb;
    dav_get_props_result propstats = { 0 };

    /*
    ** Note: ctx->doc can only be NULL for DAV_PROPFIND_IS_ALLPROP. Since
    ** dav_get_allprops() does not need to do namespace translation,
    ** we're okay.
    **
    ** Note: we cast to lose the "const". The propdb won't try to change
    ** the resource, however, since we are opening readonly.
    */
    err = dav_open_propdb(ctx->r, ctx->w.lockdb, wres->resource, 1,
                          ctx->doc ? ctx->doc->namespaces : NULL, &propdb);
    if (err != NULL) {
        /* ### do something with err! */

        if (ctx->propfind_type == DAV_PROPFIND_IS_PROP) {
            dav_get_props_result badprops = { 0 };

            /* some props were expected on this collection/resource */
            dav_cache_badprops(ctx);
            badprops.propstats = ctx->propstat_404;
            dav_stream_response(wres, 0, &badprops, ctx->scratchpool);
        }
        else {
            /* no props on this collection/resource */
            dav_stream_response(wres, HTTP_OK, NULL, ctx->scratchpool);
        }

        apr_pool_clear(ctx->scratchpool);
        return NULL;
    }
    /* ### what to do about closing the propdb on server failure? */

    if (ctx->propfind_type == DAV_PROPFIND_IS_PROP) {
        propstats = dav_get_props(propdb, ctx->doc);
    }
    else {
        dav_prop_insert what = ctx->propfind_type == DAV_PROPFIND_IS_ALLPROP
                                 ? DAV_PROP_INSERT_VALUE
                                 : DAV_PROP_INSERT_NAME;
        propstats = dav_get_allprops(propdb, what);
    }
    dav_close_propdb(propdb);

    dav_stream_response(wres, 0, &propstats, ctx->scratchpool);

    /* at this point, ctx->scratchpool has been used to stream a
       single response.  this function fully controls the pool, and
       thus has the right to clear it for the next iteration of this
       callback. */
    apr_pool_clear(ctx->scratchpool);

    return NULL;
}