void
comm_add_close_handler(int fd, CLCB * handler, void *data)
{
    debugs(5, 5, "comm_add_close_handler: FD " << fd << ", handler=" <<
           handler << ", data=" << data);

    AsyncCall::Pointer call=commCbCall(5,4, "SomeCloseHandler",
                                       CommCloseCbPtrFun(handler, data));
    comm_add_close_handler(fd, call);
}