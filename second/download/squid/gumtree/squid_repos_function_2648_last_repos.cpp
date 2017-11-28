static void
errorSendComplete(const Comm::ConnectionPointer &conn, char *, size_t size, Comm::Flag errflag, int, void *data)
{
    ErrorState *err = static_cast<ErrorState *>(data);
    debugs(4, 3, HERE << conn << ", size=" << size);

    if (errflag != Comm::ERR_CLOSING) {
        if (err->callback) {
            debugs(4, 3, "errorSendComplete: callback");
            err->callback(conn->fd, err->callback_data, size);
        } else {
            debugs(4, 3, "errorSendComplete: comm_close");
            conn->close();
        }
    }

    delete err;
}