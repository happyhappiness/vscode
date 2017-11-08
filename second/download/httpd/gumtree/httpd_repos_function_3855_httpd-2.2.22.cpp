static apr_status_t impl_pollcb_create(apr_pollcb_t *pollcb,
                                       apr_uint32_t size,
                                       apr_pool_t *p,
                                       apr_uint32_t flags)
{
    int fd;
    
#ifdef HAVE_EPOLL_CREATE1
    fd = epoll_create1(EPOLL_CLOEXEC);
#else
    fd = epoll_create(size);
#endif
    
    if (fd < 0) {
        return apr_get_netos_error();
    }

#ifndef HAVE_EPOLL_CREATE1
    {
        int flags;

        if ((flags = fcntl(fd, F_GETFD)) == -1)
            return errno;

        flags |= FD_CLOEXEC;
        if (fcntl(fd, F_SETFD, flags) == -1)
            return errno;
    }
#endif
    
    pollcb->fd = fd;
    pollcb->pollset.epoll = apr_palloc(p, size * sizeof(struct epoll_event));
    apr_pool_cleanup_register(p, pollcb, cb_cleanup, apr_pool_cleanup_null);

    return APR_SUCCESS;
}