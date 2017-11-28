static void
idnsAddMDNSNameservers()
{
    nns_mdns_count=0;

    // mDNS is disabled
    if (!Config.onoff.dns_mdns)
        return;

    // mDNS resolver addresses are explicit multicast group IPs
    if (Ip::EnableIpv6) {
        idnsAddNameserver("FF02::FB");
        nameservers[nns-1].S.port(5353);
        nameservers[nns-1].mDNSResolver = true;
        ++nns_mdns_count;
    }

    idnsAddNameserver("224.0.0.251");
    nameservers[nns-1].S.port(5353);
    nameservers[nns-1].mDNSResolver = true;

    ++nns_mdns_count;
}