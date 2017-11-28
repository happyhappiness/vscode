u_char *
snmp_pdu_decode(u_char * Packet,	/* data */
                int *Length,		/* &length */
                struct snmp_pdu * PDU)
{				/* pdu */
    u_char *bufp;
    u_char PDUType;
    u_char ASNType;
#ifdef UNUSED_CODE
    int four;
    oid objid[MAX_NAME_LEN];
#endif

    bufp = asn_parse_header(Packet, Length, &PDUType);
    if (bufp == NULL)
        ASN_PARSE_ERROR(NULL);

#ifdef DEBUG_PDU_DECODE
    snmplib_debug(8, "PDU Type: %d\n", PDUType);
#endif

    PDU->command = PDUType;
    switch (PDUType) {

#ifdef TRP_REQ_MSG
    case TRP_REQ_MSG:

        /* SNMPv1 Trap Message */

        /* enterprise */
        PDU->enterprise_length = MAX_NAME_LEN;
        bufp = asn_parse_objid(bufp, Length,
                               &ASNType, objid, &PDU->enterprise_length);
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        PDU->enterprise = (oid *) xmalloc(PDU->enterprise_length * sizeof(oid));
        if (PDU->enterprise == NULL) {
            snmp_set_api_error(SNMPERR_OS_ERR);
            return (NULL);
        }
        xmemcpy((char *) PDU->enterprise, (char *) objid,
                PDU->enterprise_length * sizeof(oid));

        /* Agent-addr */
        four = 4;
        bufp = asn_parse_string(bufp, Length,
                                &ASNType,
                                (u_char *) & PDU->agent_addr.sin_addr.s_addr,
                                &four);
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        /* Generic trap */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             (int *) &PDU->trap_type,
                             sizeof(PDU->trap_type));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        /* Specific Trap */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             (int *) &PDU->specific_type,
                             sizeof(PDU->specific_type));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        /* Timestamp */
        bufp = asn_parse_unsigned_int(bufp, Length,
                                      &ASNType,
                                      &PDU->time, sizeof(PDU->time));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);
        break;
#endif

        /**********************************************************************/

    case SNMP_PDU_GETBULK:

        /* SNMPv2 Bulk Request */

        /* request id */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->reqid, sizeof(PDU->reqid));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        /* non-repeaters */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->non_repeaters, sizeof(PDU->non_repeaters));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

        /* max-repetitions */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->max_repetitions, sizeof(PDU->max_repetitions));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);
        break;

        /**********************************************************************/

    default:

        /* Normal PDU Encoding */

        /* request id */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->reqid, sizeof(PDU->reqid));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

#ifdef DEBUG_PDU_DECODE
        snmplib_debug(8, "PDU Request ID: %d\n", PDU->reqid);
#endif

        /* error status */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->errstat, sizeof(PDU->errstat));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

#ifdef DEBUG_PDU_DECODE
        snmplib_debug(8, "PDU Error Status: %d\n", PDU->errstat);
#endif

        /* error index */
        bufp = asn_parse_int(bufp, Length,
                             &ASNType,
                             &PDU->errindex, sizeof(PDU->errindex));
        if (bufp == NULL)
            ASN_PARSE_ERROR(NULL);

#ifdef DEBUG_PDU_DECODE
        snmplib_debug(8, "PDU Error Index: %d\n", PDU->errindex);
#endif

        break;
    }

    return (bufp);
}