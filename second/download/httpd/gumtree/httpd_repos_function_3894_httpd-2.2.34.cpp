static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;
    pfd_elem_t *elem;
    int res;
    apr_status_t rv = APR_SUCCESS;

    pollset_lock_rings();

    if (!APR_RING_EMPTY(&(pollset->p->free_ring), pfd_elem_t, link)) {
        elem = APR_RING_FIRST(&(pollset->p->free_ring));
        APR_RING_REMOVE(elem, link);
    }
    else {
        elem = (pfd_elem_t *) apr_palloc(pollset->pool, sizeof(pfd_elem_t));
        APR_RING_ELEM_INIT(elem, link);
        elem->on_query_ring = 0;
    }
    elem->pfd = *descriptor;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    /* If another thread is polling, notify the kernel immediately; otherwise,
     * wait until the next call to apr_pollset_poll().
     */
    if (apr_atomic_read32(&pollset->p->waiting)) {
        res = port_associate(pollset->p->port_fd, PORT_SOURCE_FD, fd, 
                             get_event(descriptor->reqevents), (void *)elem);

        if (res < 0) {
            rv = apr_get_netos_error();
            APR_RING_INSERT_TAIL(&(pollset->p->free_ring), elem, pfd_elem_t, link);
        }
        else {
            elem->on_query_ring = 1;
            APR_RING_INSERT_TAIL(&(pollset->p->query_ring), elem, pfd_elem_t, link);
        }
    } 
    else {
        APR_RING_INSERT_TAIL(&(pollset->p->add_ring), elem, pfd_elem_t, link);
    }

    pollset_unlock_rings();

    return rv;
}