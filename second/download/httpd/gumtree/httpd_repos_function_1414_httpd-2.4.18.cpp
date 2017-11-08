static apr_status_t file_cache_create(disk_cache_conf *conf, disk_cache_file_t *file,
                                      apr_pool_t *pool)
{
    file->pool = pool;
    file->tempfile = apr_pstrcat(pool, conf->cache_root, AP_TEMPFILE, NULL);

    apr_pool_cleanup_register(pool, file, file_cache_temp_cleanup, apr_pool_cleanup_null);

    return APR_SUCCESS;
}