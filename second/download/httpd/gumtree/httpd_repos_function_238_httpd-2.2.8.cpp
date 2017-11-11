static dav_error * dav_fs_delete_walker(dav_walk_resource *wres, int calltype)
{
    dav_resource_private *info = wres->resource->info;

    /* do not attempt to remove a null resource,
     * or a collection with children
     */
    if (wres->resource->exists &&
        (!wres->resource->collection || calltype == DAV_CALLTYPE_POSTFIX)) {
        /* try to remove the resource */
        apr_status_t result;

        result = wres->resource->collection
            ? apr_dir_remove(info->pathname, wres->pool)
            : apr_file_remove(info->pathname, wres->pool);

        /*
        ** If an error occurred, then add it to multistatus response.
        ** Note that we add it for the root resource, too. It is quite
        ** possible to delete the whole darn tree, yet fail on the root.
        **
        ** (also: remember we are deleting via a postfix traversal)
        */
        if (result != APR_SUCCESS) {
            /* ### assume there is a permissions problem */

            /* ### use errno to generate DAV:responsedescription? */
            dav_add_response(wres, HTTP_FORBIDDEN, NULL);
        }
    }

    return NULL;
}