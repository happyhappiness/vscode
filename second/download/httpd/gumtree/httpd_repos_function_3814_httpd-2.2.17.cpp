static apr_status_t impl_pollcb_add(apr_pollcb_t *pollcb,
                                    apr_pollfd_t *descriptor)
{
    struct epoll_event ev;
    int ret;
    
    ev.events = get_epoll_event(descriptor->reqevents);
    ev.data.ptr = (void *)descriptor;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        ret = epoll_ctl(pollcb->fd, EPOLL_CTL_ADD,
                        descriptor->desc.s->socketdes, &ev);
    }
    else {
        ret = epoll_ctl(pollcb->fd, EPOLL_CTL_ADD,
                        descriptor->desc.f->filedes, &ev);
    }
    
    if (ret == -1) {
        return apr_get_netos_error();
    }
    
    return APR_SUCCESS;
}