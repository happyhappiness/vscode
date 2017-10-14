static void closeFile(rotate_config_t *config, apr_pool_t *pool, apr_file_t *file)
{
    if (file != NULL) {
        if (config->verbose) {
            apr_finfo_t finfo;
            apr_int32_t wanted = APR_FINFO_NAME;
            if (apr_file_info_get(&finfo, wanted, file) == APR_SUCCESS) {
                fprintf(stderr, "Closing file %s (%s)\n", finfo.name, finfo.fname);
            }
        }
        apr_file_close(file);
        if (pool) {
            apr_pool_destroy(pool);
        }
    }
}