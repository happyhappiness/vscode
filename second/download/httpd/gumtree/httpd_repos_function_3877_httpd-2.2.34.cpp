static apr_status_t impl_pollcb_add(apr_pollcb_t *pollcb,
                                    apr_pollfd_t *descriptor)
{
    if (pollcb->nelts == pollcb->nalloc) {
        return APR_ENOMEM;
    }

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        pollcb->pollset.ps[pollcb->nelts].fd = descriptor->desc.s->socketdes;
    }
    else {
#if APR_FILES_AS_SOCKETS
        pollcb->pollset.ps[pollcb->nelts].fd = descriptor->desc.f->filedes;
#else
        return APR_EBADF;
#endif
    }

    pollcb->pollset.ps[pollcb->nelts].events =
        get_event(descriptor->reqevents);
    pollcb->copyset[pollcb->nelts] = descriptor;
    pollcb->nelts++;
    
    return APR_SUCCESS;
}