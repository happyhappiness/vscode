static int prefix_stat(const char *path, apr_pool_t *pool)
{
    const char *curpath = path;
    const char *root;
    const char *slash;
    char *statpath;
    apr_status_t rv;

    rv = apr_filepath_root(&root, &curpath, APR_FILEPATH_TRUENAME, pool);

    if (rv != APR_SUCCESS) {
        return 0;
    }

    /* let's recognize slashes only, the mod_rewrite semantics are opaque
     * enough.
     */
    if ((slash = ap_strchr_c(curpath, '/')) != NULL) {
        rv = apr_filepath_merge(&statpath, root,
                                apr_pstrndup(pool, curpath,
                                             (apr_size_t)(slash - curpath)),
                                APR_FILEPATH_NOTABOVEROOT |
                                APR_FILEPATH_NOTRELATIVE, pool);
    }
    else {
        rv = apr_filepath_merge(&statpath, root, curpath,
                                APR_FILEPATH_NOTABOVEROOT |
                                APR_FILEPATH_NOTRELATIVE, pool);
    }

    if (rv == APR_SUCCESS) {
        apr_finfo_t sb;

        if (apr_stat(&sb, statpath, APR_FINFO_MIN, pool) == APR_SUCCESS) {
            return 1;
        }
    }

    return 0;
}