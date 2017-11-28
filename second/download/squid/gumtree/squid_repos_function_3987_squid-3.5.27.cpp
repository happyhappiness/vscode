void
Adaptation::Ecap::HeaderRep::removeAny(const Name &name)
{
    const http_hdr_type squidId = TranslateHeaderId(name);
    if (squidId == HDR_OTHER)
        theHeader.delByName(name.image().c_str());
    else
        theHeader.delById(squidId);

    if (squidId == HDR_CONTENT_LENGTH)
        theMessage.content_length = theHeader.getInt64(HDR_CONTENT_LENGTH);
}