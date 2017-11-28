ConnStateData *
connStateCreate(const Comm::ConnectionPointer &client, AnyP::PortCfg *port)
{
    ConnStateData *result = new ConnStateData;

    result->clientConnection = client;
    result->log_addr = client->remote;
    result->log_addr.ApplyMask(Config.Addrs.client_netmask);
    result->in.buf = (char *)memAllocBuf(CLIENT_REQ_BUF_SZ, &result->in.allocatedSize);
    result->port = cbdataReference(port);

    if (port->disable_pmtu_discovery != DISABLE_PMTU_OFF &&
            (result->transparent() || port->disable_pmtu_discovery == DISABLE_PMTU_ALWAYS)) {
#if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
        int i = IP_PMTUDISC_DONT;
        if (setsockopt(client->fd, SOL_IP, IP_MTU_DISCOVER, &i, sizeof(i)) < 0)
            debugs(33, 2, "WARNING: Path MTU discovery disabling failed on " << client << " : " << xstrerror());
#else
        static bool reported = false;

        if (!reported) {
            debugs(33, DBG_IMPORTANT, "NOTICE: Path MTU discovery disabling is not supported on your platform.");
            reported = true;
        }
#endif
    }

    typedef CommCbMemFunT<ConnStateData, CommCloseCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(33, 5, Dialer, result, ConnStateData::connStateClosed);
    comm_add_close_handler(client->fd, call);

    if (Config.onoff.log_fqdn)
        fqdncache_gethostbyaddr(client->remote, FQDN_LOOKUP_IF_MISS);

#if USE_IDENT
    if (Ident::TheConfig.identLookup) {
        ACLFilledChecklist identChecklist(Ident::TheConfig.identLookup, NULL, NULL);
        identChecklist.src_addr = client->remote;
        identChecklist.my_addr = client->local;
        if (identChecklist.fastCheck() == ACCESS_ALLOWED)
            Ident::Start(client, clientIdentDone, result);
    }
#endif

#if USE_SQUID_EUI
    if (Eui::TheConfig.euiLookup) {
        if (client->remote.IsIPv4()) {
            result->clientConnection->remoteEui48.lookup(client->remote);
        } else if (client->remote.IsIPv6()) {
            result->clientConnection->remoteEui64.lookup(client->remote);
        }
    }
#endif

    clientdbEstablished(client->remote, 1);

    result->flags.readMore = true;
    return result;
}