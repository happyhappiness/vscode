void
IcmpPinger::Recv(void)
{
    static pingerEchoData pecho;
    int n;
    int guess_size;

    memset(&pecho, '\0', sizeof(pecho));
    n = recv(socket_from_squid, &pecho, sizeof(pecho), 0);

    if (n < 0) {
        debugs(42, DBG_IMPORTANT, "Pinger exiting.");
        Close();
        exit(1);
    }

    if (0 == n) {
        /* EOF indicator */
        debugs(42, DBG_CRITICAL, HERE << "EOF encountered. Pinger exiting.\n");
        errno = 0;
        Close();
        exit(1);
    }

    guess_size = n - (sizeof(pingerEchoData) - PINGER_PAYLOAD_SZ);

    if (guess_size != pecho.psize) {
        debugs(42, 2, HERE << "size mismatch, guess=" << guess_size << ", psize=" << pecho.psize);
        /* don't process this message, but keep running */
        return;
    }

    /* pass request for ICMPv6 handing */
    if (pecho.to.isIPv6()) {
        debugs(42, 2, HERE << " Pass " << pecho.to << " off to ICMPv6 module.");
        icmp6.SendEcho(pecho.to,
                       pecho.opcode,
                       pecho.payload,
                       pecho.psize);
    }

    /* pass the packet for ICMP handling */
    else if (pecho.to.isIPv4()) {
        debugs(42, 2, HERE << " Pass " << pecho.to << " off to ICMPv4 module.");
        icmp4.SendEcho(pecho.to,
                       pecho.opcode,
                       pecho.payload,
                       pecho.psize);
    } else {
        debugs(42, DBG_IMPORTANT, HERE << " IP has unknown Type. " << pecho.to );
    }
}