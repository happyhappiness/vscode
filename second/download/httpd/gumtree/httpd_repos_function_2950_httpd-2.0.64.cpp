static char *path_remove_last_component (const char *path, apr_pool_t *pool)
{
    const char *newpath = path_canonicalize (path, pool);
    int i;
    
    for (i = (strlen(newpath) - 1); i >= 0; i--) {
        if (path[i] == PATH_SEPARATOR)
            break;
    }

    return apr_pstrndup (pool, path, (i < 0) ? 0 : i);
}