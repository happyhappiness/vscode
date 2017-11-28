static void
comm_select_dns_incoming(void)
{
    int nfds = 0;
    int fds[3];
    int nevents;
    dns_io_events = 0;

    if (DnsSocketA < 0 && DnsSocketB < 0)
        return;

    if (DnsSocketA >= 0)
        fds[nfds++] = DnsSocketA;

    if (DnsSocketB >= 0)
        fds[nfds++] = DnsSocketB;

    nevents = comm_check_incoming_select_handlers(nfds, fds);

    if (nevents < 0)
        return;

    incoming_dns_interval += Config.comm_incoming.dns_average - nevents;

    if (incoming_dns_interval < Config.comm_incoming.dns_min_poll)
        incoming_dns_interval = Config.comm_incoming.dns_min_poll;

    if (incoming_dns_interval > MAX_INCOMING_INTERVAL)
        incoming_dns_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_DNS_MAX)
        nevents = INCOMING_DNS_MAX;

    statHistCount(&statCounter.comm_dns_incoming, nevents);
}