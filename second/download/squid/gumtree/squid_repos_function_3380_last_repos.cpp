void
Adaptation::Ecap::HeaderRep::removeAny(const Name &name)
{
    const Http::HdrType squidId = TranslateHeaderId(name);
    if (squidId == Http::HdrType::OTHER)
        theHeader.delByName(name.image().c_str());
    else
        theHeader.delById(squidId);

    if (squidId == Http::HdrType::CONTENT_LENGTH)
        theMessage.content_length = theHeader.getInt64(Http::HdrType::CONTENT_LENGTH);
}