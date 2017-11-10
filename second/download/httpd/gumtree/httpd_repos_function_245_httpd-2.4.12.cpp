static dav_error * dav_fs_get_parent_resource(const dav_resource *resource,
                                              dav_resource **result_parent)
{
    dav_resource_private *ctx = resource->info;
    dav_resource_private *parent_ctx;
    dav_resource *parent_resource;
    apr_status_t rv;
    char *dirpath;
    const char *testroot;
    const char *testpath;

    /* If we're at the root of the URL space, then there is no parent. */
    if (strcmp(resource->uri, "/") == 0) {
        *result_parent = NULL;
        return NULL;
    }

    /* If given resource is root, then there is no parent.
     * Unless we can retrieve the filepath root, this is
     * intendend to fail.  If we split the root and
     * no path info remains, then we also fail.
     */
    testpath = ctx->pathname;
    rv = apr_filepath_root(&testroot, &testpath, 0, ctx->pool);
    if ((rv != APR_SUCCESS && rv != APR_ERELATIVE)
        || !testpath || !*testpath) {
        *result_parent = NULL;
        return NULL;
    }

    /* ### optimize this into a single allocation! */

    /* Create private resource context descriptor */
    parent_ctx = apr_pcalloc(ctx->pool, sizeof(*parent_ctx));

    /* ### this should go away */
    parent_ctx->pool = ctx->pool;

    dirpath = ap_make_dirstr_parent(ctx->pool, ctx->pathname);
    if (strlen(dirpath) > 1 && dirpath[strlen(dirpath) - 1] == '/')
        dirpath[strlen(dirpath) - 1] = '\0';
    parent_ctx->pathname = dirpath;

    parent_resource = apr_pcalloc(ctx->pool, sizeof(*parent_resource));
    parent_resource->info = parent_ctx;
    parent_resource->collection = 1;
    parent_resource->hooks = &dav_hooks_repository_fs;
    parent_resource->pool = resource->pool;

    if (resource->uri != NULL) {
        char *uri = ap_make_dirstr_parent(ctx->pool, resource->uri);
        if (strlen(uri) > 1 && uri[strlen(uri) - 1] == '/')
            uri[strlen(uri) - 1] = '\0';
        parent_resource->uri = uri;
    }

    rv = apr_stat(&parent_ctx->finfo, parent_ctx->pathname,
                  APR_FINFO_NORM, ctx->pool);
    if (rv == APR_SUCCESS || rv == APR_INCOMPLETE) {
        parent_resource->exists = 1;
    }

    *result_parent = parent_resource;
    return NULL;
}