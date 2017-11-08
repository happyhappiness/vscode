static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    apr_os_sock_t fd;
    int ret, i, j;
    unsigned int nget;
    pfd_elem_t *ep;
    apr_status_t rv = APR_SUCCESS;
    apr_pollfd_t fp;

    nget = 1;

    pollset_lock_rings();

    apr_atomic_inc32(&pollset->p->waiting);

    while (!APR_RING_EMPTY(&(pollset->p->add_ring), pfd_elem_t, link)) {
        ep = APR_RING_FIRST(&(pollset->p->add_ring));
        APR_RING_REMOVE(ep, link);

        if (ep->pfd.desc_type == APR_POLL_SOCKET) {
            fd = ep->pfd.desc.s->socketdes;
        }
        else {
            fd = ep->pfd.desc.f->filedes;
        }

        ret = port_associate(pollset->p->port_fd, PORT_SOURCE_FD, 
                             fd, get_event(ep->pfd.reqevents), ep);
        if (ret < 0) {
            rv = apr_get_netos_error();
            APR_RING_INSERT_TAIL(&(pollset->p->free_ring), ep, pfd_elem_t, link);
            break;
        }

        ep->on_query_ring = 1;
        APR_RING_INSERT_TAIL(&(pollset->p->query_ring), ep, pfd_elem_t, link);
    }

    pollset_unlock_rings();

    if (rv != APR_SUCCESS) {
        apr_atomic_dec32(&pollset->p->waiting);
        return rv;
    }

    rv = call_port_getn(pollset->p->port_fd, pollset->p->port_set, 
                        pollset->nalloc, &nget, timeout);

    /* decrease the waiting ASAP to reduce the window for calling 
       port_associate within apr_pollset_add() */
    apr_atomic_dec32(&pollset->p->waiting);

    (*num) = nget;
    if (nget) {

        pollset_lock_rings();

        for (i = 0, j = 0; i < nget; i++) {
            fp = (((pfd_elem_t*)(pollset->p->port_set[i].portev_user))->pfd);
            if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                fp.desc_type == APR_POLL_FILE &&
                fp.desc.f == pollset->wakeup_pipe[0]) {
                apr_pollset_drain_wakeup_pipe(pollset);
                rv = APR_EINTR;
            }
            else {
                pollset->p->result_set[j] = fp;            
                pollset->p->result_set[j].rtnevents =
                    get_revent(pollset->p->port_set[i].portev_events);

                /* If the ring element is still on the query ring, move it
                 * to the add ring for re-association with the event port
                 * later.  (It may have already been moved to the dead ring
                 * by a call to pollset_remove on another thread.)
                 */
                ep = (pfd_elem_t *)pollset->p->port_set[i].portev_user;
                if (ep->on_query_ring) {
                    APR_RING_REMOVE(ep, link);
                    ep->on_query_ring = 0;
                    APR_RING_INSERT_TAIL(&(pollset->p->add_ring), ep,
                                         pfd_elem_t, link);
                }
                j++;
            }
        }
        pollset_unlock_rings();
        if ((*num = j)) { /* any event besides wakeup pipe? */
            rv = APR_SUCCESS;
            if (descriptors) {
                *descriptors = pollset->p->result_set;
            }
        }
    }

    pollset_lock_rings();

    /* Shift all PFDs in the Dead Ring to the Free Ring */
    APR_RING_CONCAT(&(pollset->p->free_ring), &(pollset->p->dead_ring), pfd_elem_t, link);

    pollset_unlock_rings();

    return rv;
}