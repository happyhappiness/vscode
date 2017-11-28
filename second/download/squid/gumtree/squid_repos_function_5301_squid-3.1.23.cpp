int
Icmp6::Open(void)
{
    icmp_sock = socket(PF_INET6, SOCK_RAW, IPPROTO_ICMPV6);

    if (icmp_sock < 0) {
        debugs(50, 0, HERE << " icmp_sock: " << xstrerror());
        return -1;
    }

    icmp_ident = getpid() & 0xffff;
    debugs(42, 1, "pinger: ICMPv6 socket opened");

    return icmp_sock;
}