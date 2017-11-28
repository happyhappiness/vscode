void
Ipc::Forwarder::removeTimeoutEvent()
{
    if (eventFind(&Forwarder::RequestTimedOut, this))
        eventDelete(&Forwarder::RequestTimedOut, this);
}