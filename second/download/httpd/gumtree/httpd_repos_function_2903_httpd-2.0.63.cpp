apr_status_t filepath_root_case(char **rootpath, char *root, apr_pool_t *p)
{
/* See the Windows code to figure out what to do here.
    It probably checks to make sure that the root exists 
    and case it correctly according to the file system.
*/
    *rootpath = apr_pstrdup(p, root);
    return APR_SUCCESS;
}