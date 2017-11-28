u_char *
snmp_msg_Decode(u_char * Packet, int *PacketLenP,
                u_char * Community, int *CommLenP,
                int *Version, struct snmp_pdu * PDU)
{
    u_char *bufp;
    u_char type;

    bufp = asn_parse_header(Packet, PacketLenP, &type);
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Decode:Error decoding SNMP Message Header (Header)!\n");
        ASN_PARSE_ERROR(NULL);
    }
    if (type != (ASN_SEQUENCE | ASN_CONSTRUCTOR)) {
        snmplib_debug(4, "snmp_msg_Decode:Error decoding SNMP Message Header (Header)!\n");
        ASN_PARSE_ERROR(NULL);
    }
    bufp = asn_parse_int(bufp, PacketLenP,
                         &type,
                         (int *) Version, sizeof(*Version));
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Decode:Error decoding SNMP Message Header (Version)!\n");
        ASN_PARSE_ERROR(NULL);
    }
    bufp = asn_parse_string(bufp, PacketLenP, &type, Community, CommLenP);
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Decode:Error decoding SNMP Message Header (Community)!\n");
        ASN_PARSE_ERROR(NULL);
    }
    Community[*CommLenP] = '\0';

    if ((*Version != SNMP_VERSION_1) &&
            (*Version != SNMP_VERSION_2)) {

        /* Don't know how to handle this one. */
        snmplib_debug(4, "snmp_msg_Decode:Unable to parse Version %u\n", *Version);
        snmplib_debug(4, "snmp_msg_Decode:Continuing anyway\n");
    }
    /* Now that we know the header, decode the PDU */

    /* XXXXX -- More than one PDU? */
    bufp = snmp_pdu_decode(bufp, PacketLenP, PDU);
    if (bufp == NULL)
        /* snmp_pdu_decode registered failure */
        return (NULL);

    bufp = snmp_var_DecodeVarBind(bufp, PacketLenP, &(PDU->variables), *Version);
    if (bufp == NULL)
        /* snmp_var_DecodeVarBind registered failure */
        return (NULL);

    return (u_char *) bufp;
}