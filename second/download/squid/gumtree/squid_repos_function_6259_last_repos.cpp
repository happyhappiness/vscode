void
aioClose(int fd)
{
    squidaio_ctrl_t *ctrlp;

    assert(DiskThreadsIOStrategy::Instance.initialised);
    ++squidaio_counts.close_start;
    aioCancel(fd);
    ctrlp = new squidaio_ctrl_t;
    ctrlp->fd = fd;
    ctrlp->done_handler = NULL;
    ctrlp->done_handler_data = NULL;
    ctrlp->operation = _AIO_CLOSE;
    ctrlp->result.data = ctrlp;
    squidaio_close(fd, &ctrlp->result);
    dlinkAdd(ctrlp, &ctrlp->node, &used_list);
    return;
}