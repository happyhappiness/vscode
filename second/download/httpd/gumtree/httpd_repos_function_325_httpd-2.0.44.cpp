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
            dav_add_response(wres, 0, &badprops);
        }
        else {
            /* no props on this collection/resource */
            dav_add_response(wres, HTTP_OK, NULL);
        }
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

    dav_add_response(wres, 0, &propstats);

    return NULL;
}