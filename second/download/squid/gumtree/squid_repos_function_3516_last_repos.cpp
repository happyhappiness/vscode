const char *Adaptation::Icap::ModXact::virginContentData(const Adaptation::Icap::VirginBodyAct &act) const
{
    Must(act.active());
    const uint64_t dataStart = act.offset();
    Must(virginConsumed <= dataStart);
    return virgin.body_pipe->buf().content() + static_cast<size_t>(dataStart-virginConsumed);
}