void
Snmp::Forwarder::sendError(int error)
{
    debugs(49, 3, HERE);
    Snmp::Request& req = static_cast<Snmp::Request&>(*request);
    req.pdu.command = SNMP_PDU_RESPONSE;
    req.pdu.errstat = error;
    u_char buffer[SNMP_REQUEST_SIZE];
    int len = sizeof(buffer);
    snmp_build(&req.session, &req.pdu, buffer, &len);
    comm_udp_sendto(fd, req.address, buffer, len);
}