static apr_status_t impl_pollset_remove(apr_pollset_t *pollset,
                                        const apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;
    pfd_elem_t *ep;
    apr_status_t rv = APR_SUCCESS;
    int res;
    int err = 0;
    int found;

    pollset_lock_rings();

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    /* Search the add ring first.  This ring is often shorter,
     * and it often contains the descriptor being removed.  
     * (For the common scenario where apr_pollset_poll() 
     * returns activity for the descriptor and the descriptor
     * is then removed from the pollset, it will have just 
     * been moved to the add ring by apr_pollset_poll().)
     *
     * If it is on the add ring, it isn't associated with the
     * event port yet/anymore.
     */
    found = 0;
    for (ep = APR_RING_FIRST(&(pollset->p->add_ring));
         ep != APR_RING_SENTINEL(&(pollset->p->add_ring),
                                 pfd_elem_t, link);
         ep = APR_RING_NEXT(ep, link)) {

        if (descriptor->desc.s == ep->pfd.desc.s) {
            found = 1;
            APR_RING_REMOVE(ep, link);
            APR_RING_INSERT_TAIL(&(pollset->p->free_ring),
                                 ep, pfd_elem_t, link);
            break;
        }
    }

    if (!found) {
        res = port_dissociate(pollset->p->port_fd, PORT_SOURCE_FD, fd);

        if (res < 0) {
            /* The expected case for this failure is that another
             * thread's call to port_getn() returned this fd and
             * disassociated the fd from the event port, and 
             * impl_pollset_poll() is blocked on the ring lock,
             * which this thread holds.
             */
            err = errno;
            rv = APR_NOTFOUND;
        }

        for (ep = APR_RING_FIRST(&(pollset->p->query_ring));
             ep != APR_RING_SENTINEL(&(pollset->p->query_ring),
                                     pfd_elem_t, link);
             ep = APR_RING_NEXT(ep, link)) {

            if (descriptor->desc.s == ep->pfd.desc.s) {
                APR_RING_REMOVE(ep, link);
                ep->on_query_ring = 0;
                APR_RING_INSERT_TAIL(&(pollset->p->dead_ring),
                                     ep, pfd_elem_t, link);
                if (ENOENT == err) {
                    rv = APR_SUCCESS;
                }
                break;
            }
        }
    }

    pollset_unlock_rings();

    return rv;
}