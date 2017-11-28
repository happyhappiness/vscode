int
squidaio_unlink(const char *path, squidaio_result_t * resultp)
{
    squidaio_init();
    squidaio_request_t *requestp;

    requestp = (squidaio_request_t *)squidaio_request_pool->alloc();

    requestp->path = squidaio_xstrdup(path);

    requestp->resultp = resultp;

    requestp->request_type = _AIO_OP_UNLINK;

    requestp->cancelled = 0;

    resultp->result_type = _AIO_OP_UNLINK;

    squidaio_queue_request(requestp);

    return 0;
}