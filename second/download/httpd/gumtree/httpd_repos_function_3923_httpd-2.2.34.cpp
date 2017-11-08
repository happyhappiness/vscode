static apr_status_t impl_pollset_remove(apr_pollset_t *pollset,
                                        const apr_pollfd_t *descriptor)
{
    pfd_elem_t *ep;
    apr_status_t rv;
    apr_os_sock_t fd;

    pollset_lock_rings();

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    rv = APR_NOTFOUND; /* unless at least one of the specified conditions is */
    if (descriptor->reqevents & APR_POLLIN) {
        EV_SET(&pollset->p->kevent, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);

        if (kevent(pollset->p->kqueue_fd, &pollset->p->kevent, 1, NULL, 0,
                   NULL) != -1) {
            rv = APR_SUCCESS;
        }
    }

    if (descriptor->reqevents & APR_POLLOUT) {
        EV_SET(&pollset->p->kevent, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);

        if (kevent(pollset->p->kqueue_fd, &pollset->p->kevent, 1, NULL, 0,
                   NULL) != -1) {
            rv = APR_SUCCESS;
        }
    }

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

    return rv;
}