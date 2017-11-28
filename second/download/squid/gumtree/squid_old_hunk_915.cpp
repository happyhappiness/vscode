{
    debugs(16, 5, HERE);
    conn = NULL; // needed?
    mustStop("commClosed");
}

/// called when Coordinator starts processing the request
void
Mgr::Forwarder::handleRemoteAck()
{
    Ipc::Forwarder::handleRemoteAck();

    Must(entry != NULL);
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    entry->complete();
}

/// send error page
void
Mgr::Forwarder::sendError(ErrorState *error)
{
    debugs(16, 3, HERE);
    Must(error != NULL);
