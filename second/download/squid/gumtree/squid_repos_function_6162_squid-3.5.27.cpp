int

squidaio_stat(const char *path, struct stat *sb, squidaio_result_t * resultp)
{
    squidaio_init();
    squidaio_request_t *requestp;

    requestp = (squidaio_request_t *)squidaio_request_pool->alloc();

    requestp->path = (char *) squidaio_xstrdup(path);

    requestp->statp = sb;

    requestp->tmpstatp = (struct stat *) squidaio_xmalloc(sizeof(struct stat));

    requestp->resultp = resultp;

    requestp->request_type = _AIO_OP_STAT;

    requestp->cancelled = 0;

    resultp->result_type = _AIO_OP_STAT;

    squidaio_queue_request(requestp);

    return 0;
}