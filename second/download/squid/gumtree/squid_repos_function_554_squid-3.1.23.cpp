u_char *
snmp_msg_Encode(u_char * Buffer, int *BufLenP,
                u_char * Community, int CommLen,
                int Version,
                struct snmp_pdu *PDU)
{
    u_char *bufp, *tmp;
    u_char *PDUHeaderPtr, *VARHeaderPtr;
    u_char *PDUDataStart, *VARDataStart;
    u_char *MsgPtr;
    int FakeArg = 1024;

    snmplib_debug(4, "Buffer=%p BufLenP=%p, buflen=%d\n", Buffer, BufLenP,
                  *BufLenP);
    /* Header for the entire thing, with a false, large length */
    bufp = asn_build_header(Buffer, BufLenP,
                            (u_char) (ASN_SEQUENCE |
                                      ASN_CONSTRUCTOR),
                            (*BufLenP));
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Encode:Error encoding SNMP Message Header (Header)!\n");
        return (NULL);
    }
    MsgPtr = bufp;

    /* Version */
    bufp = asn_build_int(bufp, BufLenP,
                         (u_char) (ASN_UNIVERSAL |
                                   ASN_PRIMITIVE |
                                   ASN_INTEGER),
                         (int *) (&Version), sizeof(Version));
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Encode:Error encoding SNMP Message Header (Version)!\n");
        return (NULL);
    }
    snmplib_debug(8, "snmp_msg_Encode: Encoding community (%s) (%d)\n", Community, CommLen);

    /* Community */
    bufp = asn_build_string(bufp, BufLenP,
                            (u_char) (ASN_UNIVERSAL |
                                      ASN_PRIMITIVE |
                                      ASN_OCTET_STR),
                            Community, CommLen);
    if (bufp == NULL) {
        snmplib_debug(4, "snmp_msg_Encode:Error encoding SNMP Message Header (Community)!\n");
        return (NULL);
    }
    /* Encode the rest. */

    /* A nice header for this PDU.
     * Encoded with the wrong length.  We'll fix it later.
     */
    snmplib_debug(8, "snmp_msg_Encode:Encoding PDU Header at 0x%p (fake len %d) (%d bytes so far)\n",
                  bufp, *BufLenP, *BufLenP);
    PDUHeaderPtr = bufp;
    bufp = asn_build_header(bufp, BufLenP,
                            (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                            (*BufLenP));
    if (bufp == NULL)
        return (NULL);

    /* Encode this PDU. */
    PDUDataStart = bufp;
    bufp = snmp_pdu_encode(bufp, BufLenP, PDU);
    if (bufp == NULL)
        return (NULL);		/* snmp_pdu_encode registered failure */

    VARHeaderPtr = bufp;
    bufp = asn_build_header(bufp, BufLenP,
                            (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                            FakeArg);
    if (bufp == NULL)
        return (NULL);
    VARDataStart = bufp;

    /* And build the variables */
    bufp = snmp_var_EncodeVarBind(bufp, BufLenP, PDU->variables, Version);
    if (bufp == NULL)
        return (NULL);		/* snmp_var_EncodeVarBind registered failure */

    /* Cool.  Now insert the appropriate lengths.
     */
#ifdef DEBUG_MSG_ENCODE
    snmplib_debug(9, "Msg:  Vars returned 0x%x.  PDU Started at 0x%x\n",
                  bufp, PDUHeaderPtr);
    snmplib_debug(9, "MSG:  Entire PDU length is %d (0x%x - 0x%x)\n",
                  (int) (bufp - PDUDataStart), PDUHeaderPtr, bufp);
#endif
    tmp = asn_build_header(PDUHeaderPtr, &FakeArg,
                           (u_char) PDU->command,
                           (int) (bufp - PDUDataStart));
    /* Length of the PDU and Vars */
    if (tmp == NULL)
        return (NULL);

#ifdef DEBUG_MSG_ENCODE
    snmplib_debug(9, "MSG:  Entire message length is %d (0x%x - 0x%x)\n",
                  (int) (bufp - MsgPtr), MsgPtr, bufp);
#endif
    tmp = asn_build_header(Buffer,
                           &FakeArg,
                           (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                           (bufp - MsgPtr));	/* Length of everything */
    if (tmp == NULL)
        return (NULL);

    tmp = asn_build_header(VARHeaderPtr,
                           &FakeArg,
                           (u_char) (ASN_SEQUENCE | ASN_CONSTRUCTOR),
                           (bufp - VARDataStart));	/* Length of everything */
    if (tmp == NULL)
        return (NULL);

    *BufLenP = (bufp - Buffer);
    return (u_char *) bufp;
}