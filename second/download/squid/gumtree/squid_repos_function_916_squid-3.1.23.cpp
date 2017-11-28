void
comm_accept(int fd, AsyncCall::Pointer &call)
{
    debugs(5, 5, "comm_accept: FD " << fd << " AsyncCall: " << call);
    assert(isOpen(fd));

    fdc_table[fd].subscribe(call);
}