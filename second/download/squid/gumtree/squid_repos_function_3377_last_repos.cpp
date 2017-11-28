bool
Adaptation::Ecap::HeaderRep::hasAny(const Name &name) const
{
    const Http::HdrType squidId = TranslateHeaderId(name);
    return squidId == Http::HdrType::OTHER ?
           theHeader.hasNamed(name.image().c_str(), name.image().size()) :
           static_cast<bool>(theHeader.has(squidId));
}