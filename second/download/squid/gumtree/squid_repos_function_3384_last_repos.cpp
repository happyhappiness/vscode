Http::HdrType
Adaptation::Ecap::HeaderRep::TranslateHeaderId(const Name &name)
{
    if (name.assignedHostId())
        return static_cast<Http::HdrType>(name.hostId());
    return Http::HdrType::OTHER;
}