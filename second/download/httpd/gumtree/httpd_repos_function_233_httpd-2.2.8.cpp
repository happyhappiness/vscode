static dav_error * dav_fs_create_collection(dav_resource *resource)
{
    dav_resource_private *ctx = resource->info;
    apr_status_t status;

    status = apr_dir_make(ctx->pathname, APR_OS_DEFAULT, ctx->pool);
    if (APR_STATUS_IS_ENOSPC(status)) {
        return dav_new_error(ctx->pool, HTTP_INSUFFICIENT_STORAGE, 0,
                             "There is not enough storage to create "
                             "this collection.");
    }
    else if (APR_STATUS_IS_ENOENT(status)) {
        return dav_new_error(ctx->pool, HTTP_CONFLICT, 0,
                             "Cannot create collection; intermediate "
                             "collection does not exist.");
    }
    else if (status != APR_SUCCESS) {
        /* ### refine this error message? */
        return dav_new_error(ctx->pool, HTTP_FORBIDDEN, 0,
                             "Unable to create collection.");
    }

    /* update resource state to show it exists as a collection */
    resource->exists = 1;
    resource->collection = 1;

    return NULL;
}