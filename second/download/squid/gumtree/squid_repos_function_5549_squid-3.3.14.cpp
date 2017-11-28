int
squidaio_close(int fd, squidaio_result_t * resultp)
{
    squidaio_request_t *requestp;

    requestp = (squidaio_request_t *)squidaio_request_pool->alloc();

    requestp->fd = fd;

    requestp->resultp = resultp;

    requestp->request_type = _AIO_OP_CLOSE;

    requestp->cancelled = 0;

    resultp->result_type = _AIO_OP_CLOSE;

    squidaio_queue_request(requestp);

    return 0;
}