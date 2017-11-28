static void
snmpConstructReponse(snmp_request_t * rq)
{

    struct snmp_pdu *RespPDU;

    debugs(49, 5, "snmpConstructReponse: Called.");
    RespPDU = snmpAgentResponse(rq->PDU);
    snmp_free_pdu(rq->PDU);

    if (RespPDU != NULL) {
        snmp_build(&rq->session, RespPDU, rq->outbuf, &rq->outlen);
        comm_udp_sendto(rq->sock, rq->from, rq->outbuf, rq->outlen);
        snmp_free_pdu(RespPDU);
    }
}