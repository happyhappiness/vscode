static apr_status_t impl_pollcb_create(apr_pollcb_t *pollcb,
                                       apr_uint32_t size,
                                       apr_pool_t *p,
                                       apr_uint32_t flags)
{
    int fd;
    
    fd = kqueue();
    if (fd < 0) {
        return apr_get_netos_error();
    }

    {
        int flags;
        apr_status_t rv;

        if ((flags = fcntl(fd, F_GETFD)) == -1) {
            rv = errno;
            close(fd);
            pollcb->fd = -1;
            return rv;
        }

        flags |= FD_CLOEXEC;
        if (fcntl(fd, F_SETFD, flags) == -1) {
            rv = errno;
            close(fd);
            pollcb->fd = -1;
            return rv;
        }
    }
 
    pollcb->fd = fd;
    pollcb->pollset.ke = (struct kevent *)apr_pcalloc(p, 2 * size * sizeof(struct kevent));
    apr_pool_cleanup_register(p, pollcb, cb_cleanup, apr_pool_cleanup_null);
    
    return APR_SUCCESS;
}