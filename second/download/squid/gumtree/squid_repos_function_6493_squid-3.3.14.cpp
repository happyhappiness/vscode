void
Mgr::Forwarder::handleException(const std::exception& e)
{
    if (entry != NULL && httpRequest != NULL && Comm::IsConnOpen(conn))
        sendError(new ErrorState(ERR_INVALID_RESP, HTTP_INTERNAL_SERVER_ERROR, httpRequest));
    Ipc::Forwarder::handleException(e);
}