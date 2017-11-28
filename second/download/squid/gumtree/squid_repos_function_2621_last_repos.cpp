XactionInitiator::Initiators
XactionInitiator::ParseInitiators(const char *name)
{
    typedef std::map<std::string, XactionInitiator::Initiators> InitiatorsMap;
    static InitiatorsMap SupportedInitiators = {
        {"client", initClient},
        {"peer-pool", initPeerPool},
        {"certificate-fetching", initCertFetcher},
        {"esi", initEsi},
        {"cache-digest", initCacheDigest},
        {"server", initServer},
        {"htcp", initHtcp},
        {"icp", initIcp},
        {"icmp", initIcmp},
        {"asn", initAsn},
        {"ipc", initIpc},
        {"adaptation", initAdaptation},
        {"icon", initIcon},
        {"peer-mcast", initPeerMcast},
        {"internal", InternalInitiators()},
        {"all", AllInitiators()}
    };
    const auto it = SupportedInitiators.find(name);
    if (it != SupportedInitiators.cend())
        return it->second;

    debugs(28, DBG_CRITICAL, "FATAL: Invalid transaction_initiator value near " << name);
    self_destruct();
    return 0;
}