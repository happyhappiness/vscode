void
Mgr::Forwarder::handleTimeout()
{
    sendError(new ErrorState(ERR_LIFETIME_EXP, HTTP_REQUEST_TIMEOUT, httpRequest));
    Ipc::Forwarder::handleTimeout();
}