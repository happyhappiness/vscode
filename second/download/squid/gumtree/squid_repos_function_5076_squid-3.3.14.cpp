void
Comm::TcpAcceptor::unsubscribe(const char *reason)
{
    debugs(5, 5, HERE << status() << " AsyncCall Subscription " << theCallSub << " removed: " << reason);
    theCallSub = NULL;
}