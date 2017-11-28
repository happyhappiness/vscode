void
comm_write(int fd, const char *buf, int size, IOCB * handler, void *handler_data, FREE * free_func)
{
    AsyncCall::Pointer call = commCbCall(5,5, "SomeCommWriteHander",
                                         CommIoCbPtrFun(handler, handler_data));

    comm_write(fd, buf, size, call, free_func);
}