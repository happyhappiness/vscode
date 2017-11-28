void
Adaptation::Ecap::HeaderRep::add(const Name &name, const Value &value)
{
    const http_hdr_type squidId = TranslateHeaderId(name); // HDR_OTHER OK
    HttpHeaderEntry *e = new HttpHeaderEntry(squidId, name.image().c_str(),
            value.toString().c_str());
    theHeader.addEntry(e);

    if (squidId == HDR_CONTENT_LENGTH)
        theMessage.content_length = theHeader.getInt64(HDR_CONTENT_LENGTH);
}