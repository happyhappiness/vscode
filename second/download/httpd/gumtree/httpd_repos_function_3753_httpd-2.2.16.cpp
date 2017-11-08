static apr_status_t pollset_cleanup(void *p)
{
    apr_pollset_t *pollset = (apr_pollset_t *) p;
    if (pollset->provider->cleanup) {
        (*pollset->provider->cleanup)(pollset);
    }
    if (pollset->flags & APR_POLLSET_WAKEABLE) {
        /* Close both sides of the wakeup pipe */
        if (pollset->wakeup_pipe[0]) {
#if APR_FILES_AS_SOCKETS
            apr_file_close(pollset->wakeup_pipe[0]);
#else
            apr_file_socket_pipe_close(pollset->wakeup_pipe[0]);
#endif
            pollset->wakeup_pipe[0] = NULL;
        }
        if (pollset->wakeup_pipe[1]) {
#if APR_FILES_AS_SOCKETS
            apr_file_close(pollset->wakeup_pipe[1]);
#else
            apr_file_socket_pipe_close(pollset->wakeup_pipe[1]);
#endif
            pollset->wakeup_pipe[1] = NULL;
        }
    }

    return APR_SUCCESS;
}