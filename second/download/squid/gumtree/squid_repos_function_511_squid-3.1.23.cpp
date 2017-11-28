int
snmp_coexist_V2toV1(struct snmp_pdu *PDU)
{
    /* Per 3.1.1:
     */
    switch (PDU->command) {

    case SNMP_PDU_GET:
    case SNMP_PDU_GETNEXT:
#ifdef SNMP_PDU_SET
    case SNMP_PDU_SET:
#endif
        return (1);
        break;

    case SNMP_PDU_GETBULK:
        PDU->non_repeaters = 0;
        PDU->max_repetitions = 0;
        PDU->command = SNMP_PDU_GETNEXT;
        return (1);
        break;

    default:
        snmplib_debug(2, "Unable to translate PDU %d to SNMPv1!\n", PDU->command);
        snmp_set_api_error(SNMPERR_PDU_TRANSLATION);
        return (0);
    }
}