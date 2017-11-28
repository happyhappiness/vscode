int Adaptation::Icap::Options::ttl() const
{
    Must(valid());
    return theTTL >= 0 ? theTTL : TheConfig.default_options_ttl;
}