static apr_status_t impl_pollcb_remove(apr_pollcb_t *pollcb,
                                       apr_pollfd_t *descriptor)
{
    apr_status_t rv;
    struct kevent ev;
    apr_os_sock_t fd;
    
    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    rv = APR_NOTFOUND; /* unless at least one of the specified conditions is */
    if (descriptor->reqevents & APR_POLLIN) {
        EV_SET(&ev, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        
        if (kevent(pollcb->fd, &ev, 1, NULL, 0, NULL) != -1) {
            rv = APR_SUCCESS;
        }
    }
    
    if (descriptor->reqevents & APR_POLLOUT) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        
        if (kevent(pollcb->fd, &ev, 1, NULL, 0, NULL) != -1) {
            rv = APR_SUCCESS;
        }
    }
    
    return rv;
}