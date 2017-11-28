static void
squidaio_do_close(squidaio_request_t * requestp)
{
    if ((requestp->ret = close(requestp->fd)) < 0) {
        debugs(43, 0, "squidaio_do_close: FD " << requestp->fd << ", errno " << errno);
        close(requestp->fd);
    }

    requestp->err = errno;
}