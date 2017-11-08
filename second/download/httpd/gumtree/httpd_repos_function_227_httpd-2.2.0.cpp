static dav_error * dav_fs_close_stream(dav_stream *stream, int commit)
{
    apr_file_close(stream->f);

    if (!commit) {
        if (apr_file_remove(stream->pathname, stream->p) != APR_SUCCESS) {
            /* ### use a better description? */
            return dav_new_error(stream->p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                 "There was a problem removing (rolling "
                                 "back) the resource "
                                 "when it was being closed.");
        }
    }

    return NULL;
}