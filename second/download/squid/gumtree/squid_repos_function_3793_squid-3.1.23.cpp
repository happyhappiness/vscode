protocol_t
Adaptation::Ecap::FirstLineRep::TranslateProtocolId(const Name &name)
{
    if (name.assignedHostId())
        return static_cast<protocol_t>(name.hostId());
    return PROTO_NONE; // no PROTO_OTHER
}