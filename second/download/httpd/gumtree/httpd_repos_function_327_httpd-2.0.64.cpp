static dav_error * dav_label_walker(dav_walk_resource *wres, int calltype)
{
    dav_label_walker_ctx *ctx = wres->walk_ctx;
    dav_error *err = NULL;

    /* Check the state of the resource: must be a version or
     * non-checkedout version selector
     */
    /* ### need a general mechanism for reporting precondition violations
     * ### (should be returning XML document for 403/409 responses)
     */
    if (wres->resource->type != DAV_RESOURCE_TYPE_VERSION &&
        (wres->resource->type != DAV_RESOURCE_TYPE_REGULAR
         || !wres->resource->versioned)) {
        err = dav_new_error(ctx->w.pool, HTTP_CONFLICT, 0,
                            "<DAV:must-be-version-or-version-selector/>");
    }
    else if (wres->resource->working) {
        err = dav_new_error(ctx->w.pool, HTTP_CONFLICT, 0,
                            "<DAV:must-not-be-checked-out/>");
    }
    else {
        /* do the label operation */
        if (ctx->label_op == DAV_LABEL_REMOVE)
            err = (*ctx->vsn_hooks->remove_label)(wres->resource, ctx->label);
        else
            err = (*ctx->vsn_hooks->add_label)(wres->resource, ctx->label,
                                               ctx->label_op == DAV_LABEL_SET);
    }

    if (err != NULL) {
        /* ### need utility routine to add response with description? */
        dav_add_response(wres, err->status, NULL);
        wres->response->desc = err->desc;
    }

    return NULL;
}