static void
resolveDestination(Ip::Address &iaddr)
{
    struct addrinfo *AI = NULL;

    debugVerbose(2, "Transport detected: IPv4" <<
                 ((Ip::EnableIpv6 & IPV6_SPECIAL_V4MAPPING) ? "-mapped " : "") <<
                 (Ip::EnableIpv6 == IPV6_OFF ? "-only" : " and IPv6") <<
                 ((Ip::EnableIpv6 & IPV6_SPECIAL_SPLITSTACK) ? " split-stack" : ""));

    if (Transport::Config.localHost) {
        debugVerbose(2, "Resolving " << Transport::Config.localHost << " ...");

        if ( !iaddr.GetHostByName(Transport::Config.localHost) ) {
            std::cerr << "ERROR: Cannot resolve " << Transport::Config.localHost << ": Host unknown." << std::endl;
            exit(1);
        }
    } else {
        debugVerbose(2, "Resolving " << Transport::Config.hostname << " ...");
        /* Process the remote host name to locate the Protocol required
           in case we are being asked to link to another version of squid */
        if ( !iaddr.GetHostByName(Transport::Config.hostname) ) {
            std::cerr << "ERROR: Cannot resolve " << Transport::Config.hostname << ": Host unknown." << std::endl;
            exit(1);
        }
    }

    iaddr.getAddrInfo(AI);
    if ((conn = socket(AI->ai_family, AI->ai_socktype, 0)) < 0) {
        std::cerr << "ERROR: could not open socket to " << iaddr << std::endl;
        Ip::Address::FreeAddr(AI);
        exit(1);
    }
    Ip::Address::FreeAddr(AI);

    if (Transport::Config.localHost) {
        if (client_comm_bind(conn, iaddr) < 0) {
            std::cerr << "ERROR: could not bind socket to " << iaddr << std::endl;
            exit(1);
        }

        iaddr.setEmpty();

        debugVerbose(2, "Resolving... " << Transport::Config.hostname);

        if ( !iaddr.GetHostByName(Transport::Config.hostname) ) {
            std::cerr << "ERROR: Cannot resolve " << Transport::Config.hostname << ": Host unknown." << std::endl;
            exit(1);
        }
    }

    iaddr.port(Transport::Config.port);
}