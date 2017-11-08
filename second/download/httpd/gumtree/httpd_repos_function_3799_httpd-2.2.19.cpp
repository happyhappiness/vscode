static apr_status_t impl_pollcb_remove(apr_pollcb_t *pollcb,
                                       apr_pollfd_t *descriptor)
{
    int fd, ret;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    ret = port_dissociate(pollcb->fd, PORT_SOURCE_FD, fd);

    if (ret < 0) {
        return APR_NOTFOUND;
    }

    return APR_SUCCESS;
}