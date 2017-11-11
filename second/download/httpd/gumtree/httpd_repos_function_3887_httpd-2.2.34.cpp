apr_status_t asio_pollset_remove(apr_pollset_t *pollset,
                                        const apr_pollfd_t *descriptor)
{
    DBG_BUFF
    asio_elem_t *elem;
    apr_status_t rv = APR_SUCCESS;
    apr_pollset_private_t *priv = pollset->p;
    struct aiocb cancel_a;   /* AIO_CANCEL is synchronous, so autodata works fine */

    int fd;

    DBG(2, "entered\n");

    if (!(pollset->flags & APR_POLLSET_THREADSAFE)) {
        return posix_remove(pollset, descriptor);
    }

    pollset_lock_rings();

#if DEBUG
    assert(descriptor->desc_type == APR_POLL_SOCKET);
#endif
    /* zOS 1.12 doesn't support files for async i/o */
    fd = descriptor->desc.s->socketdes;

    elem = apr_hash_get(priv->elems, &(fd), sizeof(int));
    if (elem == NULL) {
        DBG1(1, "couldn't find fd %d\n", fd);
        rv = APR_NOTFOUND;
    } else {
        DBG1(5, "hash found fd %d\n", fd);
        /* delete this fd from the hash */
        apr_hash_set(priv->elems, &(fd), sizeof(int), NULL);

        if (elem->state == ASIO_INIT) {
            /* asyncio call to cancel */
            cancel_a.aio_cmd = AIO_CANCEL;
            cancel_a.aio_buf = &elem->a;   /* point to original aiocb */

            cancel_a.aio_cflags  = 0;
            cancel_a.aio_cflags2 = 0;

            /* we want the original aiocb to show up on the pollset message queue 
             * before recycling its memory to eliminate race conditions
             */

            rv = asyncio(&cancel_a);
            DBG1(4, "asyncio returned %d\n", rv);

#if DEBUG
            assert(rv == 1);
#endif
        }
        elem->state = ASIO_REMOVED;
        rv = APR_SUCCESS;
    }

    DBG1(2, "exiting, rv: %d\n", rv);

    pollset_unlock_rings();

    return rv;
}