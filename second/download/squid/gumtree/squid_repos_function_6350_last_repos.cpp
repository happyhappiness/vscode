static void
squidaio_debug(squidaio_request_t * request)
{
    switch (request->request_type) {

    case _AIO_OP_OPEN:
        debugs(43, 5, "OPEN of " << request->path << " to FD " << request->ret);
        break;

    case _AIO_OP_READ:
        debugs(43, 5, "READ on fd: " << request->fd);
        break;

    case _AIO_OP_WRITE:
        debugs(43, 5, "WRITE on fd: " << request->fd);
        break;

    case _AIO_OP_CLOSE:
        debugs(43, 5, "CLOSE of fd: " << request->fd);
        break;

    case _AIO_OP_UNLINK:
        debugs(43, 5, "UNLINK of " << request->path);
        break;

    default:
        break;
    }
}