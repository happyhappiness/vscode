static apr_status_t create_wakeup_pipe(apr_pollset_t *pollset)
{
    apr_status_t rv;

    if ((rv = apr_file_socket_pipe_create(&pollset->wakeup_pipe[0],
                                          &pollset->wakeup_pipe[1],
                                          pollset->pool)) != APR_SUCCESS)
        return rv;

    pollset->wakeup_pfd.p = pollset->pool;
    pollset->wakeup_pfd.reqevents = APR_POLLIN;
    pollset->wakeup_pfd.desc_type = APR_POLL_FILE;
    pollset->wakeup_pfd.desc.f = pollset->wakeup_pipe[0];

    return apr_pollset_add(pollset, &pollset->wakeup_pfd);
}