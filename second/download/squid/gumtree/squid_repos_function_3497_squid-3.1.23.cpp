ConnStateData *
connStateCreate(const IpAddress &peer, const IpAddress &me, int fd, http_port_list *port)
{
    ConnStateData *result = new ConnStateData;

    result->peer = peer;
    result->log_addr = peer;
    result->log_addr.ApplyMask(Config.Addrs.client_netmask);
    result->me = me;
    result->fd = fd;
    result->in.buf = (char *)memAllocBuf(CLIENT_REQ_BUF_SZ, &result->in.allocatedSize);
    result->port = cbdataReference(port);

    if (port->intercepted || port->spoof_client_ip) {
        IpAddress client, dst;

        if (IpInterceptor.NatLookup(fd, me, peer, client, dst) == 0) {
            result->me = client;
            result->peer = dst;
            result->transparent(true);
        }
    }

    if (port->disable_pmtu_discovery != DISABLE_PMTU_OFF &&
            (result->transparent() || port->disable_pmtu_discovery == DISABLE_PMTU_ALWAYS)) {
#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
        int i = IP_PMTUDISC_DONT;
        setsockopt(fd, SOL_IP, IP_MTU_DISCOVER, &i, sizeof i);

#else

        static int reported = 0;

        if (!reported) {
            debugs(33, 1, "Notice: httpd_accel_no_pmtu_disc not supported on your platform");
            reported = 1;
        }

#endif

    }

    result->flags.readMoreRequests = true;
    return result;
}