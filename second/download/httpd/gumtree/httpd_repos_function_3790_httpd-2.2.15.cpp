static apr_status_t impl_pollcb_remove(apr_pollcb_t *pollcb,
                                       apr_pollfd_t *descriptor)
{
    apr_status_t rv = APR_SUCCESS;
    struct epoll_event ev = {0}; /* ignored, but must be passed with
                                  * kernel < 2.6.9
                                  */
    int ret = -1;
    
    if (descriptor->desc_type == APR_POLL_SOCKET) {
        ret = epoll_ctl(pollcb->fd, EPOLL_CTL_DEL,
                        descriptor->desc.s->socketdes, &ev);
    }
    else {
        ret = epoll_ctl(pollcb->fd, EPOLL_CTL_DEL,
                        descriptor->desc.f->filedes, &ev);
    }
    
    if (ret < 0) {
        rv = APR_NOTFOUND;
    }
    
    return rv;
}