{
    sendError(new ErrorState(ERR_LIFETIME_EXP, Http::scRequestTimeout, httpRequest));
    Ipc::Forwarder::handleTimeout();
}

void
Mgr::Forwarder::handleException(const std::exception& e)
{
    if (entry != NULL && httpRequest != NULL && Comm::IsConnOpen(conn))
        sendError(new ErrorState(ERR_INVALID_RESP, Http::scInternalServerError, httpRequest));
    Ipc::Forwarder::handleException(e);
}

/// called when the client socket gets closed by some external force
void
Mgr::Forwarder::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(16, 5, HERE);
    conn = NULL; // needed?
    mustStop("commClosed");
}

/// send error page
void
Mgr::Forwarder::sendError(ErrorState *error)
{
    debugs(16, 3, HERE);
    Must(error != NULL);
