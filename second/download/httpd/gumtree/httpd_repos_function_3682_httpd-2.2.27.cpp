apr_status_t apr_file_flush_locked(apr_file_t *thefile)
{
    apr_status_t rv = APR_SUCCESS;

    if (thefile->direction == 1 && thefile->bufpos) {
        apr_ssize_t written = 0, ret;

        do {
            ret = write(thefile->filedes, thefile->buffer + written,
                        thefile->bufpos - written);
            if (ret > 0)
                written += ret;
        } while (written < thefile->bufpos &&
                 (ret > 0 || (ret == -1 && errno == EINTR)));
        if (ret == -1) {
            rv = errno;
        } else {
            thefile->filePtr += written;
            thefile->bufpos = 0;
        }
    }

    return rv;
}