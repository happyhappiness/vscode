apr_status_t filepath_root_case(char **rootpath, char *root, apr_pool_t *p)
{
    char path[APR_PATH_MAX];

    strcpy(path, root);
    if (path[1] == ':')
        path[0] = apr_toupper(path[0]);
    *rootpath = apr_pstrdup(p, path);
    return APR_SUCCESS;
}