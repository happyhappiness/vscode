static apr_status_t safe_file_rename(disk_cache_conf *conf,
                                     const char *src, const char *dest,
                                     apr_pool_t *pool)
{
    apr_status_t rv;

    rv = apr_file_rename(src, dest, pool);

    if (rv != APR_SUCCESS) {
        int i;

        for (i = 0; i < 2 && rv != APR_SUCCESS; i++) {
            /* 1000 micro-seconds aka 0.001 seconds. */
            apr_sleep(1000);

            rv = mkdir_structure(conf, dest, pool);
            if (rv != APR_SUCCESS)
                continue;

            rv = apr_file_rename(src, dest, pool);
        }
    }

    return rv;
}