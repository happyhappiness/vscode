void
comm_add_close_handler(int fd, AsyncCall::Pointer &call)
{
    debugs(5, 5, "comm_add_close_handler: FD " << fd << ", AsyncCall=" << call);

    /*TODO:Check for a similar scheduled AsyncCall*/
//    for (c = fd_table[fd].closeHandler; c; c = c->next)
//        assert(c->handler != handler || c->data != data);

    call->setNext(fd_table[fd].closeHandler);

    fd_table[fd].closeHandler = call;
}