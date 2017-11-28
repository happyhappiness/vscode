static void
squidaio_do_stat(squidaio_request_t * requestp)
{
    requestp->ret = stat(requestp->path, requestp->tmpstatp);
    requestp->err = errno;
}