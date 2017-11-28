int
commSetTimeout(int fd, int timeout, PF * handler, void *data)
{
    AsyncCall::Pointer call;
    debugs(5, 3, HERE << "FD " << fd << " timeout " << timeout);
    if (handler != NULL)
        call=commCbCall(5,4, "SomeTimeoutHandler", CommTimeoutCbPtrFun(handler, data));
    else
        call = NULL;
    return commSetTimeout(fd, timeout, call);
}