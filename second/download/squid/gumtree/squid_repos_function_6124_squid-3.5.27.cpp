static void
squidaio_do_close(squidaio_request_t * requestp)
{
    requestp->ret = close(requestp->fd);
    requestp->err = errno;
}