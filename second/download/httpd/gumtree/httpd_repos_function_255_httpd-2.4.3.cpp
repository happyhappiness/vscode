static dav_error * dav_fs_remove_resource(dav_resource *resource,
                                          dav_response **response)
{
    apr_status_t status;
    dav_resource_private *info = resource->info;

    *response = NULL;

    /* if a collection, recursively remove it and its children,
     * including the state dirs
     */
    if (resource->collection) {
        dav_walk_params params = { 0 };
        dav_error *err = NULL;
        dav_response *multi_status;

        params.walk_type = (DAV_WALKTYPE_NORMAL
                            | DAV_WALKTYPE_HIDDEN
                            | DAV_WALKTYPE_POSTFIX);
        params.func = dav_fs_delete_walker;
        params.pool = info->pool;
        params.root = resource;

        if ((err = dav_fs_walk(&params, DAV_INFINITY,
                               &multi_status)) != NULL) {
            /* on a "real" error, then just punt. nothing else to do. */
            return err;
        }

        if ((*response = multi_status) != NULL) {
            /* some multistatus responses exist. wrap them in a 207 */
            return dav_new_error(info->pool, HTTP_MULTI_STATUS, 0, 0,
                                 "Error(s) occurred on some resources during "
                                 "the deletion process.");
        }

        /* no errors... update resource state */
        resource->exists = 0;
        resource->collection = 0;

        return NULL;
    }

    /* not a collection; remove the file and its properties */
    if ((status = apr_file_remove(info->pathname, info->pool)) != APR_SUCCESS) {
        /* ### put a description in here */
        return dav_new_error(info->pool, HTTP_FORBIDDEN, 0, status, NULL);
    }

    /* update resource state */
    resource->exists = 0;
    resource->collection = 0;

    /* remove properties and return its result */
    return dav_fs_deleteset(info->pool, resource);
}