size_t Adaptation::Icap::ModXact::virginContentSize(const Adaptation::Icap::VirginBodyAct &act) const
{
    Must(act.active());
    // asbolute start of unprocessed data
    const uint64_t dataStart = act.offset();
    // absolute end of buffered data
    const uint64_t dataEnd = virginConsumed + virgin.body_pipe->buf().contentSize();
    Must(virginConsumed <= dataStart && dataStart <= dataEnd);
    return static_cast<size_t>(dataEnd - dataStart);
}