void Ipc::Strand::handleSnmpRequest(const Snmp::Request& request)
{
    debugs(54, 6, HERE);
    Snmp::SendResponse(request.requestId, request.pdu);
}