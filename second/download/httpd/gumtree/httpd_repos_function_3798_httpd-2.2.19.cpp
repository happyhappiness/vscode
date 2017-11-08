static apr_status_t impl_pollcb_add(apr_pollcb_t *pollcb,
                                    apr_pollfd_t *descriptor)
{
    int ret, fd;

    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    ret = port_associate(pollcb->fd, PORT_SOURCE_FD, fd,
                         get_event(descriptor->reqevents), descriptor);

    if (ret == -1) {
        return apr_get_netos_error();
    }

    return APR_SUCCESS;
}