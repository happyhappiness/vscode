int
snmp_build(session, pdu, packet, out_length)
struct snmp_session *session;
struct snmp_pdu *pdu;
u_char *packet;
int *out_length;
{
    u_char *bufp;

    bufp = snmp_msg_Encode(packet, out_length,
                           session->community, session->community_len,
                           session->Version,
                           pdu);
    snmplib_debug(8, "LIBSNMP: snmp_build():  Packet len %d (requid %d)\n",
                  *out_length, pdu->reqid);

    if (bufp == NULL)
        return (-1);

    return (0);
}