struct snmp_pdu *
snmp_pdu_clone(struct snmp_pdu *Src) {
    struct snmp_pdu *Dest;

#if DEBUG_PDU
    snmplib_debug(8, "PDU %x:  Cloning\n", (unsigned int) Src);
#endif

    Dest = (struct snmp_pdu *) xmalloc(sizeof(struct snmp_pdu));
    if (Dest == NULL) {
        snmp_set_api_error(SNMPERR_OS_ERR);
        return (NULL);
    }
    memcpy((char *) Dest, (char *) Src, sizeof(struct snmp_pdu));

#if DEBUG_PDU
    snmplib_debug(8, "PDU %x:  Created %x\n", (unsigned int) Src, (unsigned int) Dest);
#endif
    return (Dest);
}