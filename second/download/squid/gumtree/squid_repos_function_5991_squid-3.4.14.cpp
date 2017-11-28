void
Snmp::Inquirer::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(49, 5, HERE);
    Must(!Comm::IsConnOpen(conn) || conn->fd == params.conn->fd);
    conn = NULL;
    mustStop("commClosed");
}