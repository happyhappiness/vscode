time_t Adaptation::Icap::Options::expire() const
{
    Must(valid());
    return theTimestamp + ttl();
}