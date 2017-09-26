
    return apr_file_read(thefile, ch, &nbytes);
}

APR_DECLARE(apr_status_t) apr_file_puts(const char *str, apr_file_t *thefile)
{
    return apr_file_write_full(thefile, str, strlen(str), NULL);
}

APR_DECLARE(apr_status_t) apr_file_flush(apr_file_t *thefile)
{
    if (thefile->buffered) {
        apr_int64_t written = 0;

        if (thefile->direction == 1 && thefile->bufpos) {
            do {
                written = write(thefile->filedes, thefile->buffer, thefile->bufpos);
            } while (written == (apr_int64_t)-1 && errno == EINTR);
            if (written == (apr_int64_t)-1) {
                return errno;
            }
            thefile->filePtr += written;
            thefile->bufpos = 0;
        }
    }
    /* There isn't anything to do if we aren't buffering the output
     * so just return success.
     */
    return APR_SUCCESS; 
}

APR_DECLARE(apr_status_t) apr_file_gets(char *str, int len, apr_file_t *thefile)
{
    apr_status_t rv = APR_SUCCESS; /* get rid of gcc warning */
    apr_size_t nbytes;
