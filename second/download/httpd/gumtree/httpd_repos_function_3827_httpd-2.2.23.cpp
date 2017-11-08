static apr_status_t impl_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    if (pollset->nelts == pollset->nalloc) {
        return APR_ENOMEM;
    }

    pollset->p->query_set[pollset->nelts] = *descriptor;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        pollset->p->pollset[pollset->nelts].fd = descriptor->desc.s->socketdes;
    }
    else {
#if APR_FILES_AS_SOCKETS
        pollset->p->pollset[pollset->nelts].fd = descriptor->desc.f->filedes;
#else
        if ((pollset->flags & APR_POLLSET_WAKEABLE) &&
            descriptor->desc.f == pollset->wakeup_pipe[0])
            pollset->p->pollset[pollset->nelts].fd = (SOCKET)descriptor->desc.f->filedes;
        else
            return APR_EBADF;
#endif
    }
    pollset->p->pollset[pollset->nelts].events =
        get_event(descriptor->reqevents);
    pollset->nelts++;

    return APR_SUCCESS;
}