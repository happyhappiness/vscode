static apr_status_t impl_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    int rs;
    apr_uint32_t i, j;
    struct timeval tv, *tvptr;
    fd_set readset, writeset, exceptset;
    apr_status_t rv = APR_SUCCESS;

#ifdef WIN32
    /* On Win32, select() must be presented with at least one socket to
     * poll on, or select() will return WSAEINVAL.  So, we'll just
     * short-circuit and bail now.
     */
    if (pollset->nelts == 0) {
        (*num) = 0;
        if (timeout > 0) {
            apr_sleep(timeout);
            return APR_TIMEUP;
        }
        return APR_SUCCESS;
    }
#endif

    if (timeout < 0) {
        tvptr = NULL;
    }
    else {
        tv.tv_sec = (long) apr_time_sec(timeout);
        tv.tv_usec = (long) apr_time_usec(timeout);
        tvptr = &tv;
    }

    memcpy(&readset, &(pollset->p->readset), sizeof(fd_set));
    memcpy(&writeset, &(pollset->p->writeset), sizeof(fd_set));
    memcpy(&exceptset, &(pollset->p->exceptset), sizeof(fd_set));

#ifdef NETWARE
    if (HAS_PIPES(pollset->p->set_type)) {
        rs = pipe_select(pollset->p->maxfd + 1, &readset, &writeset, &exceptset,
                         tvptr);
    }
    else
#endif
        rs = select(pollset->p->maxfd + 1, &readset, &writeset, &exceptset,
                    tvptr);

    (*num) = rs;
    if (rs < 0) {
        return apr_get_netos_error();
    }
    if (rs == 0) {
        return APR_TIMEUP;
    }
    j = 0;
    for (i = 0; i < pollset->nelts; i++) {
        apr_os_sock_t fd;
        if (pollset->p->query_set[i].desc_type == APR_POLL_SOCKET) {
            fd = pollset->p->query_set[i].desc.s->socketdes;
        }
        else {
            if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
                pollset->p->query_set[i].desc.f == pollset->wakeup_pipe[0]) {
                apr_pollset_drain_wakeup_pipe(pollset);
                rv = APR_EINTR;
                continue;
            }
            else {
#if !APR_FILES_AS_SOCKETS
                return APR_EBADF;
#else
                fd = pollset->p->query_set[i].desc.f->filedes;
#endif
            }
        }
        if (FD_ISSET(fd, &readset) || FD_ISSET(fd, &writeset) ||
            FD_ISSET(fd, &exceptset)) {
            pollset->p->result_set[j] = pollset->p->query_set[i];
            pollset->p->result_set[j].rtnevents = 0;
            if (FD_ISSET(fd, &readset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLIN;
            }
            if (FD_ISSET(fd, &writeset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLOUT;
            }
            if (FD_ISSET(fd, &exceptset)) {
                pollset->p->result_set[j].rtnevents |= APR_POLLERR;
            }
            j++;
        }
    }
    if (((*num) = j) != 0)
        rv = APR_SUCCESS;

    if (descriptors)
        *descriptors = pollset->p->result_set;
    return rv;
}