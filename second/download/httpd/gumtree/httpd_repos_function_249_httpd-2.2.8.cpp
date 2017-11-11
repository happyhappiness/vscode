static dav_error *dav_fs_patch_rollback(const dav_resource *resource,
                                        int operation,
                                        void *context,
                                        dav_liveprop_rollback *rollback_ctx)
{
    apr_fileperms_t perms = resource->info->finfo.protection & ~APR_UEXECUTE;
    int value = rollback_ctx != NULL;

    /* assert: prop == executable. operation == SET. */

    /* restore the executable bit */
    if (value)
        perms |= APR_UEXECUTE;

    if (apr_file_perms_set(resource->info->pathname, perms) != APR_SUCCESS) {
        return dav_new_error(resource->info->pool,
                             HTTP_INTERNAL_SERVER_ERROR, 0,
                             "After a failure occurred, the resource's "
                             "executable flag could not be restored.");
    }

    /* restore the resource's state */
    resource->info->finfo.protection = perms;

    return NULL;
}