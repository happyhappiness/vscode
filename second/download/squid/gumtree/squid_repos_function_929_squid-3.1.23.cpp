void
AcceptLimiter::defer (int fd, Acceptor::AcceptorFunction *aFunc, void *data)
{
    debugs(5, 5, "AcceptLimiter::defer: FD " << fd << " handler: " << (void*)aFunc);
    Acceptor temp;
    temp.theFunction = aFunc;
    temp.acceptFD = fd;
    temp.theData = data;
    deferred.push_back(temp);
}