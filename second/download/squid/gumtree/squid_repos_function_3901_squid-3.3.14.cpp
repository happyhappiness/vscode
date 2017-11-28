http_hdr_type
Adaptation::Ecap::HeaderRep::TranslateHeaderId(const Name &name)
{
    if (name.assignedHostId())
        return static_cast<http_hdr_type>(name.hostId());
    return HDR_OTHER;
}