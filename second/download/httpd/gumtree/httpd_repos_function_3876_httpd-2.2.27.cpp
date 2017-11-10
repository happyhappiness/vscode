static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    struct epoll_event ev = {0};
    int ret = -1;
    pfd_elem_t *elem = NULL;
    apr_status_t rv = APR_SUCCESS;

    ev.events = get_epoll_event(descriptor->reqevents);

    if (pollset->flags & APR_POLLSET_NOCOPY) {
        ev.data.ptr = (void *)descriptor;
    }
    else {
        pollset_lock_rings();

        if (!APR_RING_EMPTY(&(pollset->p->free_ring), pfd_elem_t, link)) {
            elem = APR_RING_FIRST(&(pollset->p->free_ring));
            APR_RING_REMOVE(elem, link);
        }
        else {
            elem = (pfd_elem_t *) apr_palloc(pollset->pool, sizeof(pfd_elem_t));
            APR_RING_ELEM_INIT(elem, link);
        }
        elem->pfd = *descriptor;
        ev.data.ptr = elem;
    }
    if (descriptor->desc_type == APR_POLL_SOCKET) {
        ret = epoll_ctl(pollset->p->epoll_fd, EPOLL_CTL_ADD,
                        descriptor->desc.s->socketdes, &ev);
    }
    else {
        ret = epoll_ctl(pollset->p->epoll_fd, EPOLL_CTL_ADD,
                        descriptor->desc.f->filedes, &ev);
    }

    if (0 != ret) {
        rv = apr_get_netos_error();
    }

    if (!(pollset->flags & APR_POLLSET_NOCOPY)) {
        if (rv != APR_SUCCESS) {
            APR_RING_INSERT_TAIL(&(pollset->p->free_ring), elem, pfd_elem_t, link);
        }
        else {
            APR_RING_INSERT_TAIL(&(pollset->p->query_ring), elem, pfd_elem_t, link);
        }
        pollset_unlock_rings();
    }

    return rv;
}