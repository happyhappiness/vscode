static apr_status_t asio_pollset_add(apr_pollset_t *pollset,
                                     const apr_pollfd_t *descriptor)
{
    DBG_BUFF
    asio_elem_t *elem;
    apr_status_t rv = APR_SUCCESS;
    apr_pollset_private_t *priv = pollset->p;

    pollset_lock_rings();
    DBG(2, "entered\n");

    if (pollset->flags & APR_POLLSET_THREADSAFE) {

        if (!APR_RING_EMPTY(&(priv->free_ring), asio_elem_t, link)) {
            elem = APR_RING_FIRST(&(priv->free_ring));
            APR_RING_REMOVE(elem, link);
            DBG1(3, "used recycled memory at %08p\n", elem);
            elem->state = ASIO_INIT;
            elem->a.aio_cflags = 0;
        }
        else {
            elem = (asio_elem_t *) apr_pcalloc(pollset->pool, sizeof(asio_elem_t));
            DBG1(3, "alloced new memory at %08p\n", elem);

            elem->a.aio_notifytype = AIO_MSGQ;
            elem->a.aio_msgev_qid  = priv->msg_q;
            DBG1(5, "aio_msgev_quid = %d \n", elem->a.aio_msgev_qid);
            elem->a.aio_msgev_size = sizeof(asio_elem_t *);
            elem->a.aio_msgev_flag = 0;     /* wait if queue is full */
            elem->a.aio_msgev_addr = &(elem->msg);
            elem->a.aio_buf        = &(elem->os_pfd);
            elem->a.aio_nbytes     = 1;     /* number of pfds to poll */
            elem->msg.msg_type     = 1;
            elem->msg.msg_elem     = elem;
        }

        /* z/OS only supports async I/O for sockets for now */
        elem->os_pfd.fd = descriptor->desc.s->socketdes;

        APR_RING_ELEM_INIT(elem, link);
        elem->a.aio_cmd       = AIO_SELPOLL;
        elem->a.aio_cflags    &= ~AIO_OK2COMPIMD; /* not OK to complete inline*/
        elem->pfd             = *descriptor;
        elem->os_pfd.events   = get_event(descriptor->reqevents);

        if (0 != asyncio(&elem->a)) {
            rv = errno;
            DBG3(4, "pollset %p asio failed fd %d, errno %p\n",
                     pollset, elem->os_pfd.fd, rv);
#if DEBUG
            perror(__FUNCTION__ " asio failure");
#endif
        }
        else {
            DBG2(4, "good asio call, adding fd %d to pollset %p\n",
                     elem->os_pfd.fd, pollset);

            pollset->nelts++;
            apr_hash_set(priv->elems, &(elem->os_pfd.fd), sizeof(int), elem);
        }
    }
    else {
        /* APR_POLLSET_THREADSAFE isn't set.  use POSIX poll in case
         * pipes or files are used with this pollset
         */

        rv = posix_add(pollset, descriptor);
    }

    DBG1(2, "exiting, rv = %d\n", rv);

    pollset_unlock_rings();
    return rv;
}