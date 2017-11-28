static void
squidaio_do_unlink(squidaio_request_t * requestp)
{
    requestp->ret = unlink(requestp->path);
    requestp->err = errno;
}