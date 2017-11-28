void
Snmp::SendResponse(unsigned int requestId, const Pdu& pdu)
{
    debugs(49, 5, HERE);
    // snmpAgentResponse() can modify arg
    Pdu tmp = pdu;
    Snmp::Response response(requestId);
    snmp_pdu* response_pdu = NULL;
    try {
        response_pdu = snmpAgentResponse(&tmp);
        Must(response_pdu != NULL);
        response.pdu = static_cast<Pdu&>(*response_pdu);
        snmp_free_pdu(response_pdu);
    } catch (const std::exception& e) {
        debugs(49, DBG_CRITICAL, HERE << e.what());
        response.pdu.command = SNMP_PDU_RESPONSE;
        response.pdu.errstat = SNMP_ERR_GENERR;
    }
    Ipc::TypedMsgHdr message;
    response.pack(message);
    Ipc::SendMessage(Ipc::coordinatorAddr, message);
}