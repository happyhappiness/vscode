void
comm_accept(int fd, IOACB *handler, void *handler_data)
{
    debugs(5, 5, "comm_accept: FD " << fd << " handler: " << (void*)handler);
    assert(isOpen(fd));

    AsyncCall::Pointer call = commCbCall(5,5, "SomeCommAcceptHandler",
                                         CommAcceptCbPtrFun(handler, handler_data));
    fdc_table[fd].subscribe(call);
}