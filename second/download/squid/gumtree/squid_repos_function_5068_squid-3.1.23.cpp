static void
squidaio_do_write(squidaio_request_t * requestp)
{
    requestp->ret = write(requestp->fd, requestp->bufferp, requestp->buflen);
    requestp->err = errno;
}