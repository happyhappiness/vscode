static void
snmpDecodePacket(snmp_request_t * rq)
{
    struct snmp_pdu *PDU;
    u_char *Community;
    u_char *buf = rq->buf;
    int len = rq->len;
    int allow = 0;

    debugs(49, 5, HERE << "Called.");
    PDU = snmp_pdu_create(0);
    /* Allways answer on SNMPv1 */
    rq->session.Version = SNMP_VERSION_1;
    Community = snmp_parse(&rq->session, PDU, buf, len);

    /* Check if we have explicit permission to access SNMP data.
     * default (set above) is to deny all */
    if (Community && Config.accessList.snmp) {
        ACLFilledChecklist checklist(Config.accessList.snmp, NULL, NULL);
        checklist.src_addr = rq->from;
        checklist.snmp_community = (char *) Community;
        allow = checklist.fastCheck();
    }

    if ((snmp_coexist_V2toV1(PDU)) && (Community) && (allow)) {
        rq->community = Community;
        rq->PDU = PDU;
        debugs(49, 5, "snmpAgentParse: reqid=[" << PDU->reqid << "]");
        snmpConstructReponse(rq);
    } else {
        debugs(49, 1, HERE << "Failed SNMP agent query from : " << rq->from);
        snmp_free_pdu(PDU);
    }

    if (Community)
        xfree(Community);
}