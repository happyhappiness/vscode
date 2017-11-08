static apr_status_t impl_pollcb_create(apr_pollcb_t *pollcb,
                                       apr_uint32_t size,
                                       apr_pool_t *p,
                                       apr_uint32_t flags)
{
    pollcb->fd = port_create();

    if (pollcb->fd < 0) {
        return apr_get_netos_error();
    }

    {
        int flags;

        if ((flags = fcntl(pollcb->fd, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl(pollcb->fd, F_SETFD, flags) == -1)
            return errno;
    }

    pollcb->pollset.port = apr_palloc(p, size * sizeof(port_event_t));
    apr_pool_cleanup_register(p, pollcb, cb_cleanup, apr_pool_cleanup_null);

    return APR_SUCCESS;
}