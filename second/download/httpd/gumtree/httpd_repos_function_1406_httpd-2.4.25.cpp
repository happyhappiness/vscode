static apr_status_t mkdir_structure(disk_cache_conf *conf, const char *file, apr_pool_t *pool)
{
    apr_status_t rv;
    char *p;

    for (p = (char*)file + conf->cache_root_len + 1;;) {
        p = strchr(p, '/');
        if (!p)
            break;
        *p = '\0';

        rv = apr_dir_make(file,
                          APR_UREAD|APR_UWRITE|APR_UEXECUTE, pool);
        if (rv != APR_SUCCESS && !APR_STATUS_IS_EEXIST(rv)) {
            return rv;
        }
        *p = '/';
        ++p;
    }
    return APR_SUCCESS;
}