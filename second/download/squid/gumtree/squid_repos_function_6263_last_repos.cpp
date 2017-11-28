void

aioStat(char *path, struct stat *sb, AIOCB * callback, void *callback_data)
{
    squidaio_ctrl_t *ctrlp;

    assert(DiskThreadsIOStrategy::Instance.initialised);
    ++squidaio_counts.stat_start;
    ctrlp = new squidaio_ctrl_t;
    ctrlp->fd = -2;
    ctrlp->done_handler = callback;
    ctrlp->done_handler_data = cbdataReference(callback_data);
    ctrlp->operation = _AIO_STAT;
    ctrlp->result.data = ctrlp;
    squidaio_stat(path, sb, &ctrlp->result);
    dlinkAdd(ctrlp, &ctrlp->node, &used_list);
    return;
}