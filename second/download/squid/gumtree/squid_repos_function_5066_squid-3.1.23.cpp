static void
squidaio_do_read(squidaio_request_t * requestp)
{
    lseek(requestp->fd, requestp->offset, requestp->whence);
    requestp->ret = read(requestp->fd, requestp->bufferp, requestp->buflen);
    requestp->err = errno;
}