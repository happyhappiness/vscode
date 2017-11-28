void
aioCancel(int fd)
{
    squidaio_ctrl_t *ctrlp;
    dlink_node *m, *next;

    assert(DiskThreadsIOStrategy::Instance.initialised);
    ++squidaio_counts.cancel;

    for (m = used_list.head; m; m = next) {
        next = m->next;
        ctrlp = (squidaio_ctrl_t *)m->data;

        if (ctrlp->fd != fd)
            continue;

        squidaio_cancel(&ctrlp->result);

        if (ctrlp->done_handler) {
            AIOCB *callback = ctrlp->done_handler;
            void *cbdata;
            ctrlp->done_handler = NULL;
            debugs(32, DBG_IMPORTANT, "this be aioCancel. Danger ahead!");

            if (cbdataReferenceValidDone(ctrlp->done_handler_data, &cbdata))
                callback(fd, cbdata, NULL, -2, -2);

            /* free data if requested to aioWrite() */
            if (ctrlp->free_func)
                ctrlp->free_func(ctrlp->bufp);

            /* free temporary read buffer */
            if (ctrlp->operation == _AIO_READ)
                squidaio_xfree(ctrlp->bufp, ctrlp->len);
        }

        dlinkDelete(m, &used_list);
        DiskThreadsIOStrategy::Instance.squidaio_ctrl_pool->freeOne(ctrlp);
    }
}