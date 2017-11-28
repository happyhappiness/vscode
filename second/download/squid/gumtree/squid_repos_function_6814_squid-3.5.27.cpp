void
Ipc::Forwarder::RequestTimedOut(void* param)
{
    debugs(54, 3, HERE);
    Must(param != NULL);
    Forwarder* fwdr = static_cast<Forwarder*>(param);
    // use async call to enable job call protection that time events lack
    CallJobHere(54, 5, fwdr, Forwarder, requestTimedOut);
}