static void
squidaio_do_open(squidaio_request_t * requestp)
{
    requestp->ret = open(requestp->path, requestp->oflag, requestp->mode);
    requestp->err = errno;
}