void
Snmp::Forwarder::noteCommClosed(const CommCloseCbParams& params)
{
    debugs(49, 5, HERE);
    Must(fd == params.fd);
    fd = -1;
    mustStop("commClosed");
}