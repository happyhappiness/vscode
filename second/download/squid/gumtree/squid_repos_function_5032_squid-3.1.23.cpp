void
aioRead(int fd, off_t offset, size_t len, AIOCB * callback, void *callback_data)
{
    squidaio_ctrl_t *ctrlp;
    int seekmode;

    assert(DiskThreadsIOStrategy::Instance.initialised);
    squidaio_counts.read_start++;
    ctrlp = (squidaio_ctrl_t *)DiskThreadsIOStrategy::Instance.squidaio_ctrl_pool->alloc();
    ctrlp->fd = fd;
    ctrlp->done_handler = callback;
    ctrlp->done_handler_data = cbdataReference(callback_data);
    ctrlp->operation = _AIO_READ;
    ctrlp->len = len;
    ctrlp->bufp = (char *)squidaio_xmalloc(len);

    if (offset >= 0)
        seekmode = SEEK_SET;
    else {
        seekmode = SEEK_CUR;
        offset = 0;
    }

    ctrlp->result.data = ctrlp;
    squidaio_read(fd, ctrlp->bufp, len, offset, seekmode, &ctrlp->result);
    dlinkAdd(ctrlp, &ctrlp->node, &used_list);
    return;
}