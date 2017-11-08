static dav_error * dav_fs_copymove_walker(dav_walk_resource *wres,
                                          int calltype)
{
    dav_fs_copymove_walk_ctx *ctx = wres->walk_ctx;
    dav_resource_private *srcinfo = wres->resource->info;
    dav_resource_private *dstinfo = ctx->res_dst->info;
    dav_error *err = NULL;

    if (wres->resource->collection) {
        if (calltype == DAV_CALLTYPE_POSTFIX) {
            /* Postfix call for MOVE. delete the source dir.
             * Note: when copying, we do not enable the postfix-traversal.
             */
            /* ### we are ignoring any error here; what should we do? */
            (void) apr_dir_remove(srcinfo->pathname, ctx->pool);
        }
        else {
            /* copy/move of a collection. Create the new, target collection */
            if (apr_dir_make(dstinfo->pathname, APR_OS_DEFAULT,
                             ctx->pool) != APR_SUCCESS) {
                /* ### assume it was a permissions problem */
                /* ### need a description here */
                err = dav_new_error(ctx->pool, HTTP_FORBIDDEN, 0, NULL);
            }
        }
    }
    else {
        err = dav_fs_copymove_file(ctx->is_move, ctx->pool, 
                                   srcinfo->pathname, dstinfo->pathname, 
                                   &ctx->work_buf);
        /* ### push a higher-level description? */
    }

    /*
    ** If we have a "not so bad" error, then it might need to go into a
    ** multistatus response.
    **
    ** For a MOVE, it will always go into the multistatus. It could be
    ** that everything has been moved *except* for the root. Using a
    ** multistatus (with no errors for the other resources) will signify
    ** this condition.
    **
    ** For a COPY, we are traversing in a prefix fashion. If the root fails,
    ** then we can just bail out now.
    */
    if (err != NULL
        && !ap_is_HTTP_SERVER_ERROR(err->status)
        && (ctx->is_move
            || !dav_fs_is_same_resource(wres->resource, ctx->root))) {
        /* ### use errno to generate DAV:responsedescription? */
        dav_add_response(wres, err->status, NULL);

        /* the error is in the multistatus now. do not stop the traversal. */
        return NULL;
    }

    return err;
}