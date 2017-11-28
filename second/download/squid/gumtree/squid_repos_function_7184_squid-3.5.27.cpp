void
Mgr::Inquirer::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(16, 5, HERE);
    Must(!Comm::IsConnOpen(conn) && params.conn.getRaw() == conn.getRaw());
    conn = NULL;
    mustStop("commClosed");
}