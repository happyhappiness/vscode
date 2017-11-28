void
dnsInit(void)
{
    static int init = 0;

    CBDATA_INIT_TYPE(nsvc);
    CBDATA_INIT_TYPE(idns_query);

    if (DnsSocketA < 0 && DnsSocketB < 0) {
        Ip::Address addrV6; // since we don't want to alter Config.Addrs.udp_* and dont have one of our own.

        if (!Config.Addrs.udp_outgoing.isNoAddr())
            addrV6 = Config.Addrs.udp_outgoing;
        else
            addrV6 = Config.Addrs.udp_incoming;

        Ip::Address addrV4 = addrV6;
        addrV4.setIPv4();

        if (Ip::EnableIpv6 && addrV6.isIPv6()) {
            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrV6);
            DnsSocketB = comm_open_listener(SOCK_DGRAM,
                                            IPPROTO_UDP,
                                            addrV6,
                                            COMM_NONBLOCKING,
                                            "DNS Socket IPv6");
        }

        if (addrV4.isIPv4()) {
            debugs(78, 2, "idnsInit: attempt open DNS socket to: " << addrV4);
            DnsSocketA = comm_open_listener(SOCK_DGRAM,
                                            IPPROTO_UDP,
                                            addrV4,
                                            COMM_NONBLOCKING,
                                            "DNS Socket IPv4");
        }

        if (DnsSocketA < 0 && DnsSocketB < 0)
            fatal("Could not create a DNS socket");

        /* Ouch... we can't call functions using debug from a debug
         * statement. Doing so messes up the internal Debug::level
         */
        if (DnsSocketB >= 0) {
            comm_local_port(DnsSocketB);
            debugs(78, DBG_IMPORTANT, "DNS Socket created at " << addrV6 << ", FD " << DnsSocketB);
            Comm::SetSelect(DnsSocketB, COMM_SELECT_READ, idnsRead, NULL, 0);
        }
        if (DnsSocketA >= 0) {
            comm_local_port(DnsSocketA);
            debugs(78, DBG_IMPORTANT, "DNS Socket created at " << addrV4 << ", FD " << DnsSocketA);
            Comm::SetSelect(DnsSocketA, COMM_SELECT_READ, idnsRead, NULL, 0);
        }
    }

    assert(0 == nns);
    idnsAddMDNSNameservers();
    bool nsFound = idnsParseNameservers();

    if (!nsFound)
        nsFound = idnsParseResolvConf();

#if _SQUID_WINDOWS_
    if (!nsFound)
        nsFound = idnsParseWIN32Registry();
#endif

    if (!nsFound) {
        debugs(78, DBG_IMPORTANT, "Warning: Could not find any nameservers. Trying to use localhost");
#if _SQUID_WINDOWS_
        debugs(78, DBG_IMPORTANT, "Please check your TCP-IP settings or /etc/resolv.conf file");
#else
        debugs(78, DBG_IMPORTANT, "Please check your /etc/resolv.conf file");
#endif

        debugs(78, DBG_IMPORTANT, "or use the 'dns_nameservers' option in squid.conf.");
        if (Ip::EnableIpv6)
            idnsAddNameserver("::1");
        idnsAddNameserver("127.0.0.1");
    }

    if (!init) {
        memDataInit(MEM_IDNS_QUERY, "idns_query", sizeof(idns_query), 0);
        memset(RcodeMatrix, '\0', sizeof(RcodeMatrix));
        idns_lookup_hash = hash_create((HASHCMP *) strcmp, 103, hash_string);
        ++init;
    }

#if WHEN_EDNS_RESPONSES_ARE_PARSED
    if (Config.onoff.ignore_unknown_nameservers && max_shared_edns > 0) {
        debugs(0, DBG_IMPORTANT, "ERROR: cannot negotiate EDNS with unknown nameservers. Disabling");
        max_shared_edns = -1; // disable if we might receive random replies.
    }
#endif

    idnsRegisterWithCacheManager();
}