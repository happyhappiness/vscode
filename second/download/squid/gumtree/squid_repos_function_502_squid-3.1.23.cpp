u_char *
snmp_pdu_encode(u_char * DestBuf, int *DestBufLen,
                struct snmp_pdu *PDU)
{
    u_char *bufp;

#ifdef DEBUG_PDU_ENCODE
    snmplib_debug(8, "PDU: Encoding %d\n", PDU->command);
#endif

    /* ASN.1 Header */
    switch (PDU->command) {

        /**********************************************************************/
#ifdef TRP_REQ_MSG
    case TRP_REQ_MSG:

        /* SNMPv1 Trap */

        /* enterprise */
        bufp = asn_build_objid(DestBuf, DestBufLen,
                               (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_OBJECT_ID),
                               (oid *) PDU->enterprise, PDU->enterprise_length);
        if (bufp == NULL)
            return (NULL);

        /* agent-addr */
        bufp = asn_build_string(bufp, DestBufLen,
                                (u_char) (SMI_IPADDRESS | ASN_PRIMITIVE),
                                (u_char *) & PDU->agent_addr.sin_addr.s_addr,
                                sizeof(PDU->agent_addr.sin_addr.s_addr));
        if (bufp == NULL)
            return (NULL);

        /* generic trap */
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             (int *) &PDU->trap_type, sizeof(PDU->trap_type));
        if (bufp == NULL)
            return (NULL);

        /* specific trap */
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             (int *) &PDU->specific_type,
                             sizeof(PDU->specific_type));
        if (bufp == NULL)
            return (NULL);

        /* timestamp */
        bufp = asn_build_unsigned_int(bufp, DestBufLen,
                                      (u_char) (SMI_TIMETICKS | ASN_PRIMITIVE),
                                      &PDU->time, sizeof(PDU->time));
        if (bufp == NULL)
            return (NULL);
        break;
#endif

        /**********************************************************************/

    case SNMP_PDU_GETBULK:

        /* SNMPv2 Bulk Request */

        /* request id */
        bufp = asn_build_int(DestBuf, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->reqid, sizeof(PDU->reqid));
        if (bufp == NULL)
            return (NULL);

        /* non-repeaters */
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->non_repeaters,
                             sizeof(PDU->non_repeaters));
        if (bufp == NULL)
            return (NULL);

        /* max-repetitions */
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->max_repetitions,
                             sizeof(PDU->max_repetitions));
        if (bufp == NULL)
            return (NULL);
        break;

        /**********************************************************************/

    default:

        /* Normal PDU Encoding */

        /* request id */
#ifdef DEBUG_PDU_ENCODE
        snmplib_debug(8, "PDU: Request ID %d (0x%x)\n", PDU->reqid, DestBuf);
#endif
        bufp = asn_build_int(DestBuf, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->reqid, sizeof(PDU->reqid));
        if (bufp == NULL)
            return (NULL);

        /* error status */
#ifdef DEBUG_PDU_ENCODE
        snmplib_debug(8, "PDU: Error Status %d (0x%x)\n", PDU->errstat, bufp);
#endif
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->errstat, sizeof(PDU->errstat));
        if (bufp == NULL)
            return (NULL);

        /* error index */
#ifdef DEBUG_PDU_ENCODE
        snmplib_debug(8, "PDU: Error index %d (0x%x)\n", PDU->errindex, bufp);
#endif
        bufp = asn_build_int(bufp, DestBufLen,
                             (u_char) (ASN_UNIVERSAL | ASN_PRIMITIVE | ASN_INTEGER),
                             &PDU->errindex, sizeof(PDU->errindex));
        if (bufp == NULL)
            return (NULL);
        break;
    }				/* End of encoding */

    return (bufp);
}