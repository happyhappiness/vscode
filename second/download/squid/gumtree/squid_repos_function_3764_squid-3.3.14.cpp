void
Ip::ProbeTransport()
{
#if USE_IPV6
    // check for usable IPv6 sockets
    int s = socket(PF_INET6, SOCK_STREAM, 0);
    if (s < 0) {
        debugs(3, 2, "IPv6 not supported on this machine. Auto-Disabled.");
        EnableIpv6 = IPV6_OFF;
        return;
    }

    // Test for v4-mapping capability
    // (AKA. the operating system supports RFC 3493 section 5.3)
#if defined(IPV6_V6ONLY)
    int tos = 0;
    if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, (char *) &tos, sizeof(int)) == 0) {
        debugs(3, 2, "Detected IPv6 hybrid or v4-mapping stack...");
        EnableIpv6 |= IPV6_SPECIAL_V4MAPPING;
    } else {
        debugs(3, 2, "Detected split IPv4 and IPv6 stacks ...");
        EnableIpv6 |= IPV6_SPECIAL_SPLITSTACK;
    }
#else
    // compliance here means they at least supply the option for compilers building code
    // even if possibly to return hard-coded -1 on use.
    debugs(3, 2, "Missing RFC 3493 compliance - attempting split IPv4 and IPv6 stacks ...");
    EnableIpv6 |= IPV6_SPECIAL_SPLITSTACK;
#endif
    close(s);

    debugs(3, 2, "IPv6 transport " << (EnableIpv6?"Enabled":"Disabled"));
#else
    debugs(3, 2, "IPv6 transport forced OFF by build parameters.");
    EnableIpv6 = IPV6_OFF;
#endif
}