AnyP::ProtocolType
Adaptation::Ecap::FirstLineRep::TranslateProtocolId(const Name &name)
{
    if (name.assignedHostId())
        return static_cast<AnyP::ProtocolType>(name.hostId());
    return AnyP::PROTO_UNKNOWN;
}