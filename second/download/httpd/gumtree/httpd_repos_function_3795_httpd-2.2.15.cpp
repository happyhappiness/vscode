static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;
    pfd_elem_t *elem;
    apr_status_t rv = APR_SUCCESS;

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

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    if (descriptor->reqevents & APR_POLLIN) {
        EV_SET(&pollset->p->kevent, fd, EVFILT_READ, EV_ADD, 0, 0, elem);

        if (kevent(pollset->p->kqueue_fd, &pollset->p->kevent, 1, NULL, 0,
                   NULL) == -1) {
            rv = apr_get_netos_error();
        }
    }

    if (descriptor->reqevents & APR_POLLOUT && rv == APR_SUCCESS) {
        EV_SET(&pollset->p->kevent, fd, EVFILT_WRITE, EV_ADD, 0, 0, elem);

        if (kevent(pollset->p->kqueue_fd, &pollset->p->kevent, 1, NULL, 0,
                   NULL) == -1) {
            rv = apr_get_netos_error();
        }
    }

    if (rv == APR_SUCCESS) {
        APR_RING_INSERT_TAIL(&(pollset->p->query_ring), elem, pfd_elem_t, link);
    }
    else {
        APR_RING_INSERT_TAIL(&(pollset->p->free_ring), elem, pfd_elem_t, link);
    }

    pollset_unlock_rings();

    return rv;
}