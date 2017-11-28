void
snmp_pdu_free(struct snmp_pdu *pdu)
{
    snmp_free_pdu(pdu);
}