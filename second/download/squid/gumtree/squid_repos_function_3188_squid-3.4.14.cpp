static void
errorSendComplete(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ErrorState *err = static_cast<ErrorState *>(data);
    debugs(4, 3, HERE << conn << ", size=" << size);

    if (errflag != COMM_ERR_CLOSING) {
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