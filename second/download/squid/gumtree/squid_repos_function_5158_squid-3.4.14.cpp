void
Comm::TcpAcceptor::subscribe(const Subscription::Pointer &aSub)
{
    debugs(5, 5, HERE << status() << " AsyncCall Subscription: " << aSub);
    unsubscribe("subscription change");
    theCallSub = aSub;
}