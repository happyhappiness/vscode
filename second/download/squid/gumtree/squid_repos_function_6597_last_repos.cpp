void
IcmpSquid::SendEcho(Ip::Address &to, int opcode, const char *payload, int len)
{
    static pingerEchoData pecho;
    int x, slen;

    /** \li Does nothing if the pinger socket is not available. */
    if (icmp_sock < 0) {
        debugs(37, 2, HERE << " Socket Closed. Aborted send to " << pecho.to << ", opcode " << opcode << ", len " << pecho.psize);
        return;
    }

    /** \li  If no payload is given or is set as NULL it will ignore payload and len */
    if (!payload)
        len = 0;

    /** \li Otherwise if len is 0, uses strlen() to detect length of payload.
     \bug This will result in part of the payload being truncated if it contains a NULL character.
     \bug Or it may result in a buffer over-run if the payload is not nul-terminated properly.
     */
    else if (payload && len == 0)
        len = strlen(payload);

    /** \li
     \bug If length specified or auto-detected is greater than the possible payload squid will die with an assert.
     \todo This should perhapse be reduced to a truncated payload? or no payload. A WARNING is due anyway.
     */
    assert(len <= PINGER_PAYLOAD_SZ);

    pecho.to = to;

    pecho.opcode = (unsigned char) opcode;

    pecho.psize = len;

    if (len > 0)
        memcpy(pecho.payload, payload, len);

    slen = sizeof(pingerEchoData) - PINGER_PAYLOAD_SZ + pecho.psize;

    debugs(37, 2, HERE << "to " << pecho.to << ", opcode " << opcode << ", len " << pecho.psize);

    x = comm_udp_send(icmp_sock, (char *)&pecho, slen, 0);

    if (x < 0) {
        int xerrno = errno;
        debugs(37, DBG_IMPORTANT, MYNAME << "send: " << xstrerr(xerrno));

        /** \li  If the send results in ECONNREFUSED or EPIPE errors from helper, will cleanly shutdown the module. */
        /** \todo This should try restarting the helper a few times?? before giving up? */
        if (xerrno == ECONNREFUSED || xerrno == EPIPE) {
            Close();
            return;
        }
        /** All other send errors are ignored. */
    } else if (x != slen) {
        debugs(37, DBG_IMPORTANT, HERE << "Wrote " << x << " of " << slen << " bytes");
    }
}