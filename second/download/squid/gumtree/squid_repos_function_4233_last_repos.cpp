const Acl::ParameterFlags &
ACLRegexData::supportedFlags() const
{
    static const Acl::ParameterFlags flags = { "-i", "+i" };
    return flags;
}