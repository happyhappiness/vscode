apr_status_t apr_unix_file_cleanup(void *thefile)
{
    apr_file_t *file = thefile;
    apr_status_t flush_rv = APR_SUCCESS, rv = APR_SUCCESS;

    if (file->buffered) {
        flush_rv = apr_file_flush(file);
    }

    rv = file_cleanup(file, 0);

    return rv != APR_SUCCESS ? rv : flush_rv;
}