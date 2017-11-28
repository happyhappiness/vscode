int
Icmp4::Open(void)
{
    icmp_sock = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (icmp_sock < 0) {
        int xerrno = errno;
        debugs(50, DBG_CRITICAL, MYNAME << " icmp_sock: " << xstrerr(xerrno));
        return -1;
    }

    icmp_ident = getpid() & 0xffff;
    debugs(42, DBG_IMPORTANT, "pinger: ICMP socket opened.");

    return icmp_sock;
}