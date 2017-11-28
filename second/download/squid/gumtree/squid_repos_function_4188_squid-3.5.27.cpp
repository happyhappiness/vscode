uint64_t Adaptation::Icap::VirginBodyAct::offset() const
{
    Must(active());
    return static_cast<uint64_t>(theStart);
}