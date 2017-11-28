void
Adaptation::Icap::ServiceRep::finalize()
{
    Adaptation::Service::finalize();

    // use /etc/services or default port if needed
    const bool have_port = cfg().port >= 0;
    if (!have_port) {
        struct servent *serv;
        if (cfg().protocol.caseCmp("icaps") == 0)
            serv = getservbyname("icaps", "tcp");
        else
            serv = getservbyname("icap", "tcp");

        if (serv) {
            writeableCfg().port = htons(serv->s_port);
        } else {
            writeableCfg().port = cfg().protocol.caseCmp("icaps") == 0 ? DEFAULT_ICAPS_PORT : DEFAULT_ICAP_PORT;
        }
    }

    if (cfg().protocol.caseCmp("icaps") == 0)
        writeableCfg().secure.encryptTransport = true;

    if (cfg().secure.encryptTransport) {
        debugs(3, DBG_IMPORTANT, "Initializing service " << cfg().resource << " SSL context");
        sslContext = writeableCfg().secure.createClientContext(true);
    }

    if (!cfg().connectionEncryption.configured())
        writeableCfg().connectionEncryption.defaultTo(cfg().secure.encryptTransport);

    theSessionFailures.configure(TheConfig.oldest_service_failure > 0 ?
                                 TheConfig.oldest_service_failure : -1);
}