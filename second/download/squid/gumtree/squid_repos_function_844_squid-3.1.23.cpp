void
comm_read(int fd, char *buf, int size, IOCB *handler, void *handler_data)
{
    AsyncCall::Pointer call = commCbCall(5,4, "SomeCommReadHandler",
                                         CommIoCbPtrFun(handler, handler_data));
    comm_read(fd, buf, size, call);
}