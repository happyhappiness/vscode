const Acl::Options &
ACLServerNameStrategy::options()
{
    static const Acl::BooleanOption ClientRequested;
    static const Acl::BooleanOption ServerProvided;
    static const Acl::BooleanOption Consensus;
    static const Acl::Options MyOptions = {
        {"--client-requested", &ClientRequested},
        {"--server-provided", &ServerProvided},
        {"--consensus", &Consensus}
    };

    ClientRequested.linkWith(&useClientRequested);
    ServerProvided.linkWith(&useServerProvided);
    Consensus.linkWith(&useConsensus);
    return MyOptions;
}