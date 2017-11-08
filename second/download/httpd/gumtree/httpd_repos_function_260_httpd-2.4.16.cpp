static dav_error * dav_fs_move_resource(
    dav_resource *src,
    dav_resource *dst,
    dav_response **response)
{
    dav_resource_private *srcinfo = src->info;
    dav_resource_private *dstinfo = dst->info;
    dav_error *err;
    apr_status_t rv;

#if DAV_DEBUG
    if (src->hooks != dst->hooks) {
        /*
        ** ### strictly speaking, this is a design error; we should not
        ** ### have reached this point.
        */
        return dav_new_error(src->info->pool, HTTP_INTERNAL_SERVER_ERROR, 0, 0,
                             "DESIGN ERROR: a mix of repositories "
                             "was passed to move_resource.");
    }
#endif


    /* try rename first */
    rv = apr_file_rename(srcinfo->pathname, dstinfo->pathname, srcinfo->pool);

    /* if we can't simply rename, then do it the hard way... */
    if (APR_STATUS_IS_EXDEV(rv)) {
        if ((err = dav_fs_copymove_resource(1, src, dst, DAV_INFINITY,
                                            response)) == NULL) {
            /* update resource states */
            dst->exists = 1;
            dst->collection = src->collection;
            src->exists = 0;
            src->collection = 0;
        }

        return err;
    }

    /* no multistatus response */
    *response = NULL;

    if (rv != APR_SUCCESS) {
        /* ### should have a better error than this. */
        return dav_new_error(srcinfo->pool, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                             "Could not rename resource.");
    }

    /* Rename did work. Update resource states and move properties as well */
    dst->exists = 1;
    dst->collection = src->collection;
    src->exists = 0;
    src->collection = 0;

    if ((err = dav_fs_copymoveset(1, src->info->pool,
                                  src, dst, NULL)) == NULL) {
        /* no error. we're done. go ahead and return now. */
        return NULL;
    }

    /* error occurred during properties move; try to put resource back */
    if (apr_file_rename(dstinfo->pathname, srcinfo->pathname,
                       srcinfo->pool) != APR_SUCCESS) {
        /* couldn't put it back! */
        return dav_push_error(srcinfo->pool,
                              HTTP_INTERNAL_SERVER_ERROR, 0,
                              "The resource was moved, but a failure "
                              "occurred during the move of its "
                              "properties. The resource could not be "
                              "restored to its original location. The "
                              "server is now in an inconsistent state.",
                              err);
    }

    /* update resource states again */
    src->exists = 1;
    src->collection = dst->collection;
    dst->exists = 0;
    dst->collection = 0;

    /* resource moved back, but properties may be inconsistent */
    return dav_push_error(srcinfo->pool,
                          HTTP_INTERNAL_SERVER_ERROR, 0,
                          "The resource was moved, but a failure "
                          "occurred during the move of its properties. "
                          "The resource was moved back to its original "
                          "location, but its properties may have been "
                          "partially moved. The server may be in an "
                          "inconsistent state.",
                          err);
}