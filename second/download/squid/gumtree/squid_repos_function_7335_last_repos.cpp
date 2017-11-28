void
Mgr::Forwarder::handleException(const std::exception &e)
{
    if (entry != NULL && httpRequest != NULL && Comm::IsConnOpen(conn))
        sendError(new ErrorState(ERR_INVALID_RESP, Http::scInternalServerError, httpRequest));
    Ipc::Forwarder::handleException(e);
}