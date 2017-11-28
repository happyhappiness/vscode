void
Ipc::Forwarder::requestTimedOut()
{
    debugs(54, 3, HERE);
    handleTimeout();
}