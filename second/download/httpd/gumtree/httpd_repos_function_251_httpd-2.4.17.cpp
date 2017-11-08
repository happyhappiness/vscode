static dav_error * dav_fs_close_stream(dav_stream *stream, int commit)
{
    apr_status_t rv;

    apr_file_close(stream->f);

    if (!commit) {
        if (stream->temppath) {
            apr_pool_cleanup_run(stream->p, stream, tmpfile_cleanup);
        }
        else if (stream->unlink_on_error) {
            if ((rv = apr_file_remove(stream->pathname, stream->p))
                != APR_SUCCESS) {
                /* ### use a better description? */
                return dav_new_error(stream->p, HTTP_INTERNAL_SERVER_ERROR, 0,
                                     rv,
                                     "There was a problem removing (rolling "
                                     "back) the resource "
                                     "when it was being closed.");
            }
        }
    }
    else if (stream->temppath) {
        rv = apr_file_rename(stream->temppath, stream->pathname, stream->p);
        if (rv) {
            return dav_new_error(stream->p, HTTP_INTERNAL_SERVER_ERROR, 0, rv,
                                 "There was a problem writing the file "
                                 "atomically after writes.");
        }
        apr_pool_cleanup_kill(stream->p, stream, tmpfile_cleanup);
    }

    return NULL;
}