void
commConnectStart(int fd, const char *host, unsigned short port, CNCB * callback, void *data)
{
    debugs(5, 5, "commConnectStart: FD " << fd << ", data " << data << ", " << host << ":" << port);
    AsyncCall::Pointer call = commCbCall(5,3,
                                         "SomeCommConnectHandler", CommConnectCbPtrFun(callback, data));
    commConnectStart(fd, host, port, call);
}