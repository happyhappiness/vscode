void Ipc::Strand::handleSnmpResponse(const Snmp::Response& response)
{
    debugs(54, 6, HERE);
    Snmp::Forwarder::HandleRemoteAck(response.requestId);
}