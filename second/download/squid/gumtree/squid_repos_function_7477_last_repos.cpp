const char *
Security::NegotiationHistory::printTlsVersion(AnyP::ProtocolVersion const &v) const
{
    if (v.protocol != AnyP::PROTO_SSL && v.protocol != AnyP::PROTO_TLS)
        return nullptr;

    static char buf[512];
    snprintf(buf, sizeof(buf), "%s/%d.%d", AnyP::ProtocolType_str[v.protocol], v.major, v.minor);
    return buf;
}