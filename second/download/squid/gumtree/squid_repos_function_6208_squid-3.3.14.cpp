bool
Ipc::Forwarder::doneAll() const
{
    debugs(54, 5, HERE);
    return request->requestId == 0;
}