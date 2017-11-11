static apr_status_t impl_pollset_remove(apr_pollset_t *pollset,
                                        const apr_pollfd_t *descriptor)
{
    pfd_elem_t *ep;
    apr_status_t rv = APR_SUCCESS;
    struct epoll_event ev = {0}; /* ignored, but must be passed with
                                  * kernel < 2.6.9
                                  */
    int ret = -1;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        ret = epoll_ctl(pollset->p->epoll_fd, EPOLL_CTL_DEL,
                        descriptor->desc.s->socketdes, &ev);
    }
    else {
        ret = epoll_ctl(pollset->p->epoll_fd, EPOLL_CTL_DEL,
                        descriptor->desc.f->filedes, &ev);
    }
    if (ret < 0) {
        rv = APR_NOTFOUND;
    }

    if (!(pollset->flags & APR_POLLSET_NOCOPY)) {
        pollset_lock_rings();

        for (ep = APR_RING_FIRST(&(pollset->p->query_ring));
             ep != APR_RING_SENTINEL(&(pollset->p->query_ring),
                                     pfd_elem_t, link);
             ep = APR_RING_NEXT(ep, link)) {
                
            if (descriptor->desc.s == ep->pfd.desc.s) {
                APR_RING_REMOVE(ep, link);
                APR_RING_INSERT_TAIL(&(pollset->p->dead_ring),
                                     ep, pfd_elem_t, link);
                break;
            }
        }

        pollset_unlock_rings();
    }

    return rv;
}