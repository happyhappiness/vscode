apr_status_t filepath_root_case(char **rootpath, char *root, apr_pool_t *p)
{
    if (root[0] && apr_islower(root[0]) && root[1] == ':') {
        *rootpath = apr_pstrdup(p, root);
        (*rootpath)[0] = apr_toupper((*rootpath)[0]);
    }
    else {
       *rootpath = root;
    }
    return APR_SUCCESS;
}