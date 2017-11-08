apr_status_t filepath_root_test(char *path, apr_pool_t *p)
{
    char drive = apr_toupper(path[0]);

    if (drive >= 'A' && drive <= 'Z' && path[1] == ':' && IS_SLASH(path[2]))
        return APR_SUCCESS;

    return APR_EBADPATH;
}