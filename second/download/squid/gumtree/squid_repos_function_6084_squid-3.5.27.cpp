void
aioWrite(int fd, off_t offset, char *bufp, size_t len, AIOCB * callback, void *callback_data, FREE * free_func)
{
    squidaio_ctrl_t *ctrlp;
    int seekmode;

    assert(DiskThreadsIOStrategy::Instance.initialised);
    ++squidaio_counts.write_start;
    ctrlp = (squidaio_ctrl_t *)DiskThreadsIOStrategy::Instance.squidaio_ctrl_pool->alloc();
    ctrlp->fd = fd;
    ctrlp->done_handler = callback;
    ctrlp->done_handler_data = cbdataReference(callback_data);
    ctrlp->operation = _AIO_WRITE;
    ctrlp->bufp = bufp;
    ctrlp->free_func = free_func;

    if (offset >= 0)
        seekmode = SEEK_SET;
    else {
        seekmode = SEEK_END;
        offset = 0;
    }

    ctrlp->result.data = ctrlp;
    squidaio_write(fd, bufp, len, offset, seekmode, &ctrlp->result);
    dlinkAdd(ctrlp, &ctrlp->node, &used_list);
}