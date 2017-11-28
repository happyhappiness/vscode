void
Snmp::Inquirer::sendResponse()
{
    debugs(49, 5, HERE);
    aggrPdu.fixAggregate();
    aggrPdu.command = SNMP_PDU_RESPONSE;
    u_char buffer[SNMP_REQUEST_SIZE];
    int len = sizeof(buffer);
    Snmp::Request& req = static_cast<Snmp::Request&>(*request);
    snmp_build(&req.session, &aggrPdu, buffer, &len);
    comm_udp_sendto(conn->fd, req.address, buffer, len);
}