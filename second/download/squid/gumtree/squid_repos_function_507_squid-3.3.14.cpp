struct snmp_pdu *
snmp_pdu_fix(struct snmp_pdu *pdu, int command) {
    return (snmp_fix_pdu(pdu, command));
}