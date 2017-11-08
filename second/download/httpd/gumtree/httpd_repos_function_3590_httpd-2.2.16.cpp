apr_status_t apr_file_flush_locked(apr_file_t *thefile)
{
    apr_status_t rv = APR_SUCCESS;

    if (thefile->direction == 1 && thefile->bufpos) {
        apr_ssize_t written;

        do {
            written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
        } while (written == -1 && errno == EINTR);
        if (written == -1) {
            rv = errno;
        } else {
            thefile->filePtr += written;
            thefile->bufpos = 0;
        }
    }

    return rv;
}