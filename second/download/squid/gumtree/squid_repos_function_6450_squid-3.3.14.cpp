void
Mgr::StoreToCommWriter::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(16, 6, HERE);
    Must(!Comm::IsConnOpen(clientConnection));
    mustStop("commClosed");
}