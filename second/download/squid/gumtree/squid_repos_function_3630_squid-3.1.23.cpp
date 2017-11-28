int
IpIntercept::SetTproxy2OutgoingAddr(int fd, const IpAddress &src)
{
    IpAddress addr;
    struct in_tproxy itp;

    src.GetInAddr(itp.v.addr.faddr);
    itp.v.addr.fport = 0;

    /* If these syscalls fail then we just fallback to connecting
     * normally by simply ignoring the errors...
     */
    itp.op = TPROXY_ASSIGN;

    addr = (struct in_addr)itp.v.addr.faddr;
    addr.SetPort(itp.v.addr.fport);

    if (setsockopt(fd, SOL_IP, IP_TPROXY, &itp, sizeof(itp)) == -1) {
        debugs(20, 1, "tproxy ip=" << addr << " ERROR ASSIGN");
        return -1;
    } else {
        itp.op = TPROXY_FLAGS;
        itp.v.flags = ITP_CONNECT;

        if (setsockopt(fd, SOL_IP, IP_TPROXY, &itp, sizeof(itp)) == -1) {
            debugs(20, 1, "tproxy ip=" << addr << " ERROR CONNECT");
            return -1;
        }
    }

    return 0;
}