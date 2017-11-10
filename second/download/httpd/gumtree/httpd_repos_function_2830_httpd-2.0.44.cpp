apr_status_t apr_dir_remove(const char *path, apr_pool_t *pool)
{
    if (rmdir(path) == 0) {
        return APR_SUCCESS;
    }
    else {
        return errno;
    }
}