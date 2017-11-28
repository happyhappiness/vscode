struct snmp_pdu *
snmp_pdu_create(int command) {
    struct snmp_pdu *pdu;

#ifdef DEBUG_PDU
    snmplib_debug(8, "PDU:  Creating\n");
#endif

    pdu = (struct snmp_pdu *) xmalloc(sizeof(struct snmp_pdu));
    if (pdu == NULL) {
        snmp_set_api_error(SNMPERR_OS_ERR);
        return (NULL);
    }
    memset((char *) pdu, '\0', sizeof(struct snmp_pdu));

    pdu->command = command;
    pdu->errstat = SNMP_DEFAULT_ERRSTAT;
    pdu->errindex = SNMP_DEFAULT_ERRINDEX;
    pdu->address.sin_addr.s_addr = SNMP_DEFAULT_ADDRESS;
    pdu->enterprise = NULL;
    pdu->enterprise_length = 0;
    pdu->variables = NULL;

#ifdef DEBUG_PDU
    snmplib_debug(8, "PDU:  Created %x\n", (unsigned int) pdu);
#endif

    return (pdu);
}