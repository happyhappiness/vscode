static dav_error * dav_fs_write_stream(dav_stream *stream,
                                       const void *buf, apr_size_t bufsize)
{
    apr_status_t status;

    status = apr_file_write_full(stream->f, buf, bufsize, NULL);
    if (APR_STATUS_IS_ENOSPC(status)) {
        return dav_new_error(stream->p, HTTP_INSUFFICIENT_STORAGE, 0, status,
                             "There is not enough storage to write to "
                             "this resource.");
    }
    else if (status != APR_SUCCESS) {
        /* ### use something besides 500? */
        return dav_new_error(stream->p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                             "An error occurred while writing to a "
                             "resource.");
    }
    return NULL;
}