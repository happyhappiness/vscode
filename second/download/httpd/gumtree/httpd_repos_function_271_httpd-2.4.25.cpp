static dav_error *dav_fs_patch_exec(const dav_resource *resource,
                                    const apr_xml_elem *elem,
                                    int operation,
                                    void *context,
                                    dav_liveprop_rollback **rollback_ctx)
{
    long value = context != NULL;
    apr_fileperms_t perms = resource->info->finfo.protection;
    apr_status_t status;
    long old_value = (perms & APR_UEXECUTE) != 0;

    /* assert: prop == executable. operation == SET. */

    /* don't do anything if there is no change. no rollback info either. */
    /* DBG2("new value=%d  (old=%d)", value, old_value); */
    if (value == old_value)
        return NULL;

    perms &= ~APR_UEXECUTE;
    if (value)
        perms |= APR_UEXECUTE;

    if ((status = apr_file_perms_set(resource->info->pathname, perms))
        != APR_SUCCESS) {
        return dav_new_error(resource->info->pool,
                             HTTP_INTERNAL_SERVER_ERROR, 0, status,
                             "Could not set the executable flag of the "
                             "target resource.");
    }

    /* update the resource and set up the rollback context */
    resource->info->finfo.protection = perms;
    *rollback_ctx = (dav_liveprop_rollback *)old_value;

    return NULL;
}