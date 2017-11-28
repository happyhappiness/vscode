void
Mgr::Forwarder::noteCommClosed(const CommCloseCbParams &)
{
    debugs(16, 5, HERE);
    conn = NULL; // needed?
    mustStop("commClosed");
}