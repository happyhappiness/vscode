int
squidaio_read(int fd, char *bufp, size_t bufs, off_t offset, int whence, squidaio_result_t * resultp)
{
    squidaio_request_t *requestp;

    requestp = (squidaio_request_t *)squidaio_request_pool->alloc();

    requestp->fd = fd;

    requestp->bufferp = bufp;

    requestp->buflen = bufs;

    requestp->offset = offset;

    requestp->whence = whence;

    requestp->resultp = resultp;

    requestp->request_type = _AIO_OP_READ;

    requestp->cancelled = 0;

    resultp->result_type = _AIO_OP_READ;

    squidaio_queue_request(requestp);

    return 0;
}