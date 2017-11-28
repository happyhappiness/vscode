int
DiskThreadsIOStrategy::callback()
{
    squidaio_result_t *resultp;
    squidaio_ctrl_t *ctrlp;
    int retval = 0;

    assert(initialised);
    ++squidaio_counts.check_callback;

    for (;;) {
        if ((resultp = squidaio_poll_done()) == NULL)
            break;

        ctrlp = (squidaio_ctrl_t *) resultp->data;

        switch (resultp->result_type) {

        case _AIO_OP_NONE:

        case _AIO_OP_OPENDIR:
            break;

        case _AIO_OP_OPEN:
            ++squidaio_counts.open_finish;
            break;

        case _AIO_OP_READ:
            ++squidaio_counts.read_finish;
            break;

        case _AIO_OP_WRITE:
            ++squidaio_counts.write_finish;
            break;

        case _AIO_OP_CLOSE:
            ++squidaio_counts.close_finish;
            break;

        case _AIO_OP_UNLINK:
            ++squidaio_counts.unlink_finish;
            break;

        case _AIO_OP_STAT:
            ++squidaio_counts.stat_finish;
            break;
        }

        if (ctrlp == NULL)
            continue;       /* XXX Should not happen */

        dlinkDelete(&ctrlp->node, &used_list);

        if (ctrlp->done_handler) {
            AIOCB *done_callback = ctrlp->done_handler;
            void *cbdata;
            ctrlp->done_handler = NULL;

            if (cbdataReferenceValidDone(ctrlp->done_handler_data, &cbdata)) {
                retval = 1; /* Return that we've actually done some work */
                done_callback(ctrlp->fd, cbdata, ctrlp->bufp,
                              ctrlp->result.aio_return, ctrlp->result.aio_errno);
            } else {
                if (ctrlp->operation == _AIO_OPEN) {
                    /* The open operation was aborted.. */
                    int fd = ctrlp->result.aio_return;

                    if (fd >= 0)
                        aioClose(fd);
                }
            }
        }

        /* free data if requested to aioWrite() */
        if (ctrlp->free_func)
            ctrlp->free_func(ctrlp->bufp);

        /* free temporary read buffer */
        if (ctrlp->operation == _AIO_READ)
            squidaio_xfree(ctrlp->bufp, ctrlp->len);

        squidaio_ctrl_pool->freeOne(ctrlp);
    }

    return retval;
}