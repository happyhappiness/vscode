}

void
Mgr::Forwarder::handleError()
{
    debugs(16, DBG_CRITICAL, "ERROR: uri " << entry->url() << " exceeds buffer size");
    sendError(new ErrorState(ERR_INVALID_URL, HTTP_REQUEST_URI_TOO_LARGE, httpRequest));
    mustStop("long URI");
}

void
Mgr::Forwarder::handleTimeout()
{
    sendError(new ErrorState(ERR_LIFETIME_EXP, HTTP_REQUEST_TIMEOUT, httpRequest));
    Ipc::Forwarder::handleTimeout();
}

void
Mgr::Forwarder::handleException(const std::exception& e)
{
    if (entry != NULL && httpRequest != NULL && Comm::IsConnOpen(conn))
        sendError(new ErrorState(ERR_INVALID_RESP, HTTP_INTERNAL_SERVER_ERROR, httpRequest));
    Ipc::Forwarder::handleException(e);
}

/// called when the client socket gets closed by some external force
void
Mgr::Forwarder::noteCommClosed(const CommCloseCbParams& params)
