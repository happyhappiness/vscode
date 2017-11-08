static apr_status_t impl_pollcb_add(apr_pollcb_t *pollcb,
                                    apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;
    struct kevent ev;
    apr_status_t rv = APR_SUCCESS;
    
    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }
    
    if (descriptor->reqevents & APR_POLLIN) {
        EV_SET(&ev, fd, EVFILT_READ, EV_ADD, 0, 0, descriptor);
        
        if (kevent(pollcb->fd, &ev, 1, NULL, 0, NULL) == -1) {
            rv = apr_get_netos_error();
        }
    }
    
    if (descriptor->reqevents & APR_POLLOUT && rv == APR_SUCCESS) {
        EV_SET(&ev, fd, EVFILT_WRITE, EV_ADD, 0, 0, descriptor);
        
        if (kevent(pollcb->fd, &ev, 1, NULL, 0, NULL) == -1) {
            rv = apr_get_netos_error();
        }
    }
    
    return rv;
}