static void
errorSendComplete(int fd, char *bufnotused, size_t size, comm_err_t errflag, int xerrno, void *data)
{
    ErrorState *err = static_cast<ErrorState *>(data);
    debugs(4, 3, "errorSendComplete: FD " << fd << ", size=" << size);

    if (errflag != COMM_ERR_CLOSING) {
        if (err->callback) {
            debugs(4, 3, "errorSendComplete: callback");
            err->callback(fd, err->callback_data, size);
        } else {
            comm_close(fd);
            debugs(4, 3, "errorSendComplete: comm_close");
        }
    }

    errorStateFree(err);
}