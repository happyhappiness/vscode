void
Ipc::Coordinator::handleSnmpResponse(const Snmp::Response& response)
{
    debugs(54, 4, HERE);
    Snmp::Inquirer::HandleRemoteAck(response);
}