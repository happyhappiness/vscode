static dav_error * dav_fs_seek_stream(dav_stream *stream, apr_off_t abs_pos)
{
    apr_status_t status;

    if ((status = apr_file_seek(stream->f, APR_SET, &abs_pos))
        != APR_SUCCESS) {
        /* ### should check whether apr_file_seek set abs_pos was set to the
         * correct position? */
        /* ### use something besides 500? */
        return dav_new_error(stream->p, HTTP_INTERNAL_SERVER_ERROR, 0, status,
                             "Could not seek to specified position in the "
                             "resource.");
    }
    return NULL;
}