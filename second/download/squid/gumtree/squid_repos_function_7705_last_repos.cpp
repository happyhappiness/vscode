u_char *
snmp_parse(struct snmp_session * session,
           struct snmp_pdu * pdu,
           u_char * data,
           int length)
{
    u_char Community[128];
    u_char *bufp;
    int CommunityLen = 128;

    /* Decode the entire message. */
    data = snmp_msg_Decode(data, &length,
                           Community, &CommunityLen,
                           &session->Version, pdu);
    if (data == NULL)
        return (NULL);

    bufp = (u_char *) xmalloc(CommunityLen + 1);
    if (bufp == NULL)
        return (NULL);

    strncpy((char *) bufp, (char *) Community, CommunityLen);
    bufp[CommunityLen] = '\0';

    session->community = bufp;
    session->community_len = CommunityLen;

    return (bufp);
}