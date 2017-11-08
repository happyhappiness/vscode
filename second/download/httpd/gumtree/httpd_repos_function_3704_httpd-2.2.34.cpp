apr_status_t apr_dir_make_recursive(const char *path, apr_fileperms_t perm,
                                           apr_pool_t *pool) 
{
    apr_status_t apr_err = 0;
    
    apr_err = apr_dir_make (path, perm, pool); /* Try to make PATH right out */
    
    if (apr_err == ENOENT) { /* Missing an intermediate dir */
        char *dir;
        
        dir = path_remove_last_component(path, pool);
        /* If there is no path left, give up. */
        if (dir[0] == '\0') {
            return apr_err;
        }

        apr_err = apr_dir_make_recursive(dir, perm, pool);
        
        if (!apr_err) 
            apr_err = apr_dir_make (path, perm, pool);
    }

    /*
     * It's OK if PATH exists. Timing issues can lead to the second
     * apr_dir_make being called on existing dir, therefore this check
     * has to come last.
     */
    if (APR_STATUS_IS_EEXIST(apr_err))
        return APR_SUCCESS;

    return apr_err;
}