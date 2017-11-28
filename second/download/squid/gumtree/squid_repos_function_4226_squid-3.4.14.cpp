bool Adaptation::Icap::Options::fresh() const
{
    return squid_curtime <= expire();
}