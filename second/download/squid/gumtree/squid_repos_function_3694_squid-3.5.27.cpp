void
ConnStateData::pinBusyConnection(const Comm::ConnectionPointer &pinServer, const HttpRequest::Pointer &request)
{
    pinConnection(pinServer, request);
}