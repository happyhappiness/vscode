static void
squidaio_do_read(squidaio_request_t * requestp)
{
    if (lseek(requestp->fd, requestp->offset, requestp->whence) >= 0)
        requestp->ret = read(requestp->fd, requestp->bufferp, requestp->buflen);
    else
        requestp->ret = -1;
    requestp->err = errno;
}