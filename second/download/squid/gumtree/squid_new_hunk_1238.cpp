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
