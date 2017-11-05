static apr_status_t remove_directory(apr_pool_t *pool, const char *dir)
{
    apr_status_t rv;
    apr_dir_t *dirp;
    apr_finfo_t dirent;

    rv = apr_dir_open(&dirp, dir, pool);
    if (APR_STATUS_IS_ENOENT(rv)) {
        return rv;
    }
    if (rv != APR_SUCCESS) {
        char errmsg[120];
        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
                dir, apr_strerror(rv, errmsg, sizeof errmsg));
        return rv;
    }

    while (apr_dir_read(&dirent, APR_FINFO_DIRENT | APR_FINFO_TYPE, dirp)
            == APR_SUCCESS) {
        if (dirent.filetype == APR_DIR) {
            if (strcmp(dirent.name, ".") && strcmp(dirent.name, "..")) {
                rv = remove_directory(pool, apr_pstrcat(pool, dir, "/",
                        dirent.name, NULL));
                /* tolerate the directory not being empty, the cache may have
                 * attempted to recreate the directory in the mean time.
                 */
                if (APR_SUCCESS != rv && APR_ENOTEMPTY != rv) {
                    break;
                }
            }
        } else {
            const char *file = apr_pstrcat(pool, dir, "/", dirent.name, NULL);
            rv = apr_file_remove(file, pool);
            if (APR_SUCCESS != rv) {
                char errmsg[120];
                apr_file_printf(errfile,
                        "Could not remove file '%s': %s" APR_EOL_STR, file,
                        apr_strerror(rv, errmsg, sizeof errmsg));
                break;
            }
        }
    }

    apr_dir_close(dirp);

    if (rv == APR_SUCCESS) {
        rv = apr_dir_remove(dir, pool);
        if (APR_ENOTEMPTY == rv) {
            rv = APR_SUCCESS;
        }
        if (rv != APR_SUCCESS) {
            char errmsg[120];
            apr_file_printf(errfile, "Could not remove directory %s: %s" APR_EOL_STR,
                    dir, apr_strerror(rv, errmsg, sizeof errmsg));
        }
    }

    return rv;
}