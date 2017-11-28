bool
Adaptation::Ecap::HeaderRep::hasAny(const Name &name) const
{
    const http_hdr_type squidId = TranslateHeaderId(name);
    // XXX: optimize to remove getByName: we do not need the value here
    return squidId == HDR_OTHER ?
           theHeader.getByName(name.image().c_str()).size() > 0:
           (bool)theHeader.has(squidId);
}