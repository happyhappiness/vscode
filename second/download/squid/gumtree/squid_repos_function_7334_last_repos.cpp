void
Mgr::Forwarder::handleTimeout()
{
    sendError(new ErrorState(ERR_LIFETIME_EXP, Http::scRequestTimeout, httpRequest));
    Ipc::Forwarder::handleTimeout();
}