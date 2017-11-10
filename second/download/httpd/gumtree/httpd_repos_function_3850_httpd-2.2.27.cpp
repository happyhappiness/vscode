static apr_status_t posix_add(apr_pollset_t      *pollset,
                              const apr_pollfd_t *descriptor)
{
    DBG_BUFF
    int fd;
    apr_pool_t  *p = pollset->pool;
    apr_pollset_private_t *priv = pollset->p;

    DBG(4, "entered\n");

    if (pollset->nelts == priv->size) {
        return APR_ENOMEM;
    }

    priv->query_set[pollset->nelts] = *descriptor;
    if (descriptor->desc_type == APR_POLL_SOCKET) {
        fd = descriptor->desc.s->socketdes;
    }
    else {
        fd = descriptor->desc.f->filedes;
    }

    priv->pollset[pollset->nelts].fd = fd;

    priv->pollset[pollset->nelts].events =
        get_event(descriptor->reqevents);

    pollset->nelts++;

    DBG2(4, "exiting, fd %d added to pollset %p\n", fd, pollset);

    return APR_SUCCESS;
}