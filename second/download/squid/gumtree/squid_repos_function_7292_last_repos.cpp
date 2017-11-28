void
Mgr::StoreToCommWriter::noteCommClosed(const CommCloseCbParams &)
{
    debugs(16, 6, HERE);
    Must(!Comm::IsConnOpen(clientConnection));
    mustStop("commClosed");
}