static void
squidaio_cleanup_request(squidaio_request_t * requestp)
{
    squidaio_result_t *resultp = requestp->resultp;
    int cancelled = requestp->cancelled;

    /* Free allocated structures and copy data back to user space if the */
    /* request hasn't been cancelled */

    switch (requestp->request_type) {

    case _AIO_OP_STAT:

        if (!cancelled && requestp->ret == 0)
            memcpy(requestp->statp, requestp->tmpstatp, sizeof(struct stat));

        squidaio_xfree(requestp->tmpstatp, sizeof(struct stat));

        squidaio_xstrfree(requestp->path);

        break;

    case _AIO_OP_OPEN:
        if (cancelled && requestp->ret >= 0)
            /* The open() was cancelled but completed */
            close(requestp->ret);

        squidaio_xstrfree(requestp->path);

        break;

    case _AIO_OP_CLOSE:
        if (cancelled && requestp->ret < 0)
            /* The close() was cancelled and never got executed */
            close(requestp->fd);

        break;

    case _AIO_OP_UNLINK:

    case _AIO_OP_OPENDIR:
        squidaio_xstrfree(requestp->path);

        break;

    case _AIO_OP_READ:
        break;

    case _AIO_OP_WRITE:
        break;

    default:
        break;
    }

    if (resultp != NULL && !cancelled) {
        resultp->aio_return = requestp->ret;
        resultp->aio_errno = requestp->err;
    }

    squidaio_request_pool->freeOne(requestp);
}