int
squidaio_open(const char *path, int oflag, mode_t mode, squidaio_result_t * resultp)
{
    squidaio_init();
    squidaio_request_t *requestp;

    requestp = (squidaio_request_t *)squidaio_request_pool->alloc();

    requestp->path = (char *) squidaio_xstrdup(path);

    requestp->oflag = oflag;

    requestp->mode = mode;

    requestp->resultp = resultp;

    requestp->request_type = _AIO_OP_OPEN;

    requestp->cancelled = 0;

    resultp->result_type = _AIO_OP_OPEN;

    squidaio_queue_request(requestp);

    return 0;
}