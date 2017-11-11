static apr_status_t dir_make_parent(char *path,
                                    apr_fileperms_t perm,
                                    apr_pool_t *pool)
{
    apr_status_t rv;
    char *ch = strrchr(path, '\\');
    if (!ch) {
        return APR_ENOENT;
    }

    *ch = '\0';
    rv = apr_dir_make (path, perm, pool); /* Try to make straight off */
    
    if (APR_STATUS_IS_ENOENT(rv)) { /* Missing an intermediate dir */
        rv = dir_make_parent(path, perm, pool);

        if (rv == APR_SUCCESS) {
            rv = apr_dir_make (path, perm, pool); /* And complete the path */
        }
    }

    *ch = '\\'; /* Always replace the slash before returning */
    return rv;
}