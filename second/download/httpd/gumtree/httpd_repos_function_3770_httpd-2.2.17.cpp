static apr_status_t create_wakeup_pipe(apr_pollset_t *pollset)
{
    apr_status_t rv;
    apr_pollfd_t fd;

    if ((rv = apr_file_socket_pipe_create(&pollset->wakeup_pipe[0],
                                          &pollset->wakeup_pipe[1],
                                          pollset->pool)) != APR_SUCCESS)
        return rv;
    fd.reqevents = APR_POLLIN;
    fd.desc_type = APR_POLL_FILE;
    fd.desc.f = pollset->wakeup_pipe[0];
    /* Add the pipe to the pollset
     */
    return apr_pollset_add(pollset, &fd);
}