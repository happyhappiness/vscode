static apr_status_t asio_pollset_poll(apr_pollset_t *pollset,
                                      apr_interval_time_t timeout,
                                      apr_int32_t *num,
                                      const apr_pollfd_t **descriptors)
{
    DBG_BUFF
    int i, ret;
    asio_elem_t *elem, *next_elem;
    struct asio_msgbuf_t msg_buff;
    struct timespec tv;
    apr_status_t rv = APR_SUCCESS;
    apr_pollset_private_t *priv = pollset->p;

    DBG(6, "entered\n"); /* chatty - traces every second w/Event */

    if ((pollset->flags & APR_POLLSET_THREADSAFE) == 0 ) {
        return posix_poll(pollset, timeout, num, descriptors);
    }

    pollset_lock_rings();
    APR_RING_INIT(&(priv->ready_ring), asio_elem_t, link);

    while (!APR_RING_EMPTY(&(priv->prior_ready_ring), asio_elem_t, link)) {
        elem = APR_RING_FIRST(&(priv->prior_ready_ring));
        DBG3(5, "pollset %p elem %p fd %d on prior ready ring\n",
                pollset,
                elem,
                elem->os_pfd.fd);

        APR_RING_REMOVE(elem, link);

        /*
         * since USS does not remember what's in our pollset, we have
         * to re-add fds which have not been apr_pollset_remove'd
         *
         * there may have been too many ready fd's to return in the
         * result set last time. re-poll inline for both cases
         */

        if (elem->state == ASIO_REMOVED) {

            /* 
             * async i/o is done since it was found on prior_ready
             * the state says the caller is done with it too 
             * so recycle the elem 
             */
             
            APR_RING_INSERT_TAIL(&(priv->free_ring), elem,
                                 asio_elem_t, link);
            continue;  /* do not re-add if it has been _removed */
        }

        elem->state = ASIO_INIT;
        elem->a.aio_cflags     = AIO_OK2COMPIMD;

        if (0 != (ret = asyncio(&elem->a))) {
            if (ret == 1) {
                DBG(4, "asyncio() completed inline\n");
                /* it's ready now */
                elem->state = ASIO_COMPLETE;
                APR_RING_INSERT_TAIL(&(priv->ready_ring), elem, asio_elem_t,
                                     link);
            }
            else {
                DBG2(1, "asyncio() failed, ret: %d, errno: %d\n",
                        ret, errno);
                pollset_unlock_rings();
                return errno;
            }
        }
        DBG1(4, "asyncio() completed rc %d\n", ret);
    }

    DBG(6, "after prior ready loop\n"); /* chatty w/timeouts, hence 6 */

    /* Gather async poll completions that have occurred since the last call */
    while (0 < msgrcv(priv->msg_q, &msg_buff, sizeof(asio_elem_t *), 0,
                      IPC_NOWAIT)) {
        process_msg(pollset, &msg_buff);
    }

    /* Suspend if nothing is ready yet. */
    if (APR_RING_EMPTY(&(priv->ready_ring), asio_elem_t, link)) {

        if (timeout >= 0) {
            tv.tv_sec  = apr_time_sec(timeout);
            tv.tv_nsec = apr_time_usec(timeout) * 1000;
        } else {
            tv.tv_sec = INT_MAX;  /* block until something is ready */
        }

        DBG2(6, "nothing on the ready ring "
                "- blocking for %d seconds %d ns\n",
                tv.tv_sec, tv.tv_nsec);

        pollset_unlock_rings();   /* allow other apr_pollset_* calls while blocked */

        if (0 >= (ret = __msgrcv_timed(priv->msg_q, &msg_buff,
                                       sizeof(asio_elem_t *), 0, NULL, &tv))) {
#if DEBUG
            if (errno == EAGAIN) {
                DBG(6, "__msgrcv_timed timed out\n"); /* timeout path, so 6 */
            }
            else {
                DBG(1, "__msgrcv_timed failed!\n");
            }
#endif
            return (errno == EAGAIN) ? APR_TIMEUP : errno;
        }

        pollset_lock_rings();

        process_msg(pollset, &msg_buff);
    }

    APR_RING_INIT(&priv->prior_ready_ring, asio_elem_t, link);

    (*num) = 0;
    elem = APR_RING_FIRST(&(priv->ready_ring));

    for (i = 0;

        i < priv->size
                && elem != APR_RING_SENTINEL(&(priv->ready_ring), asio_elem_t, link);
        i++) {
             DBG2(5, "ready ring: elem %08p, fd %d\n", elem, elem->os_pfd.fd);

             priv->result_set[i] = elem->pfd;
             priv->result_set[i].rtnevents
                                    = get_revent(elem->os_pfd.revents);
             (*num)++;

             elem = APR_RING_NEXT(elem, link);

#if DEBUG
             if (elem == APR_RING_SENTINEL(&(priv->ready_ring), asio_elem_t, link)) {
                 DBG(5, "end of ready ring reached\n");
             }
#endif
    }

    if (descriptors) {
        *descriptors = priv->result_set;
    }

    /* if the result size is too small, remember which descriptors
     * haven't had results reported yet.  we will look
     * at these descriptors on the next apr_pollset_poll call
     */

    APR_RING_CONCAT(&priv->prior_ready_ring, &(priv->ready_ring), asio_elem_t, link);

    DBG1(2, "exiting, rv = %d\n", rv);

    pollset_unlock_rings();

    return rv;
}