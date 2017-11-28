void
Mgr::Forwarder::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(16, 5, HERE);
    conn = NULL; // needed?
    mustStop("commClosed");
}