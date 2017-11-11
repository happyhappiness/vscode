static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    apr_os_sock_t fd;

    if (pollset->nelts == pollset->nalloc) {
        return APR_ENOMEM;
    }

    pollset->p->query_set[pollset->nelts] = *descriptor;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
#ifdef NETWARE
        /* NetWare can't handle mixed descriptor types in select() */
        if (HAS_PIPES(pollset->p->set_type)) {
            return APR_EBADF;
        }
        else {
            pollset->p->set_type = APR_POLL_SOCKET;
        }
#endif
        fd = descriptor->desc.s->socketdes;
    }
    else {
#if !APR_FILES_AS_SOCKETS
        if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
            descriptor->desc.f == pollset->wakeup_pipe[0])
            fd = (apr_os_sock_t)descriptor->desc.f->filedes;
        else
            return APR_EBADF;
#else
#ifdef NETWARE
        /* NetWare can't handle mixed descriptor types in select() */
        if (descriptor->desc.f->is_pipe && !HAS_SOCKETS(pollset->p->set_type)) {
            pollset->p->set_type = APR_POLL_FILE;
            fd = descriptor->desc.f->filedes;
        }
        else {
            return APR_EBADF;
        }
#else
        fd = descriptor->desc.f->filedes;
#endif
#endif
    }
#if !defined(WIN32) && !defined(NETWARE)        /* socket sets handled with array of handles */
    if (fd >= FD_SETSIZE) {
        /* XXX invent new error code so application has a clue */
        return APR_EBADF;
    }
#endif
    if (descriptor->reqevents & APR_POLLIN) {
        FD_SET(fd, &(pollset->p->readset));
    }
    if (descriptor->reqevents & APR_POLLOUT) {
        FD_SET(fd, &(pollset->p->writeset));
    }
    if (descriptor->reqevents &
        (APR_POLLPRI | APR_POLLERR | APR_POLLHUP | APR_POLLNVAL)) {
        FD_SET(fd, &(pollset->p->exceptset));
    }
    if ((int) fd > pollset->p->maxfd) {
        pollset->p->maxfd = (int) fd;
    }
    pollset->nelts++;
    return APR_SUCCESS;
}