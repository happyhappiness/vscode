void
aioUnlink(const char *path, AIOCB * callback, void *callback_data)
{
    squidaio_ctrl_t *ctrlp;
    assert(DiskThreadsIOStrategy::Instance.initialised);
    ++squidaio_counts.unlink_start;
    ctrlp = new squidaio_ctrl_t;
    ctrlp->fd = -2;
    ctrlp->done_handler = callback;
    ctrlp->done_handler_data = cbdataReference(callback_data);
    ctrlp->operation = _AIO_UNLINK;
    ctrlp->result.data = ctrlp;
    squidaio_unlink(path, &ctrlp->result);
    dlinkAdd(ctrlp, &ctrlp->node, &used_list);
}