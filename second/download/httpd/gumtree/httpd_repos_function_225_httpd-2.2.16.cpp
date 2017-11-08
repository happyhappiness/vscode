dav_error * dav_fs_dir_file_name(
    const dav_resource *resource,
    const char **dirpath_p,
    const char **fname_p)
{
    dav_resource_private *ctx = resource->info;

    if (resource->collection) {
        *dirpath_p = ctx->pathname;
        if (fname_p != NULL)
            *fname_p = NULL;
    }
    else {
        const char *testpath, *rootpath;
        char *dirpath = ap_make_dirstr_parent(ctx->pool, ctx->pathname);
        apr_size_t dirlen = strlen(dirpath);
        apr_status_t rv = APR_SUCCESS;

        testpath = dirpath;
        if (dirlen > 0) {
            rv = apr_filepath_root(&rootpath, &testpath, 0, ctx->pool);
        }

        /* remove trailing slash from dirpath, unless it's a root path
         */
        if ((rv == APR_SUCCESS && testpath && *testpath)
            || rv == APR_ERELATIVE) {
            if (dirpath[dirlen - 1] == '/') {
                dirpath[dirlen - 1] = '\0';
            }
        }

        /* ###: Looks like a response could be appropriate
         *
         * APR_SUCCESS     here tells us the dir is a root
         * APR_ERELATIVE   told us we had no root (ok)
         * APR_EINCOMPLETE an incomplete testpath told us
         *                 there was no -file- name here!
         * APR_EBADPATH    or other errors tell us this file
         *                 path is undecipherable
         */

        if (rv == APR_SUCCESS || rv == APR_ERELATIVE) {
            *dirpath_p = dirpath;
            if (fname_p != NULL)
                *fname_p = ctx->pathname + dirlen;
        }
        else {
            return dav_new_error(ctx->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "An incomplete/bad path was found in "
                                 "dav_fs_dir_file_name.");
        }
    }

    return NULL;
}