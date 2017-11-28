int
Icmp6::Open(void)
{
    icmp_sock = socket(PF_INET6, SOCK_RAW, IPPROTO_ICMPV6);

    if (icmp_sock < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << " icmp_sock: " << xstrerr(xerrno));
        return -1;
    }

    icmp_ident = getpid() & 0xffff;
    debugs(42, DBG_IMPORTANT, "pinger: ICMPv6 socket opened");

    return icmp_sock;
}