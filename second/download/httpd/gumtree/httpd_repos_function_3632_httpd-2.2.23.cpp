static apr_status_t file_cleanup(apr_file_t *file, int is_child)
{
    apr_status_t rv = APR_SUCCESS;
    int fd = file->filedes;

    /* Set file descriptor to -1 before close(), so that there is no
     * chance of returning an already closed FD from apr_os_file_get().
     */
    file->filedes = -1;

    if (close(fd) == 0) {
        /* Only the parent process should delete the file! */
        if (!is_child && (file->flags & APR_FOPEN_DELONCLOSE)) {
            unlink(file->fname);
        }
#if APR_HAS_THREADS
        if (file->thlock) {
            rv = apr_thread_mutex_destroy(file->thlock);
        }
#endif
    }
    else {
        /* Restore, close() was not successful. */
        file->filedes = fd;

        /* Are there any error conditions other than EINTR or EBADF? */
        rv = errno;
    }
#ifndef WAITIO_USES_POLL
    if (file->pollset != NULL) {
        apr_status_t pollset_rv = apr_pollset_destroy(file->pollset);
        /* If the file close failed, return its error value,
         * not apr_pollset_destroy()'s.
         */
        if (rv == APR_SUCCESS) {
            rv = pollset_rv;
        }
    }
#endif /* !WAITIO_USES_POLL */
    return rv;
}