static apr_status_t file_cache_temp_cleanup(void *dummy) {
    disk_cache_file_t *file = (disk_cache_file_t *)dummy;

    /* clean up the temporary file */
    if (file->tempfd) {
        apr_file_remove(file->tempfile, file->pool);
        file->tempfd = NULL;
    }
    file->tempfile = NULL;
    file->pool = NULL;

    return APR_SUCCESS;
}