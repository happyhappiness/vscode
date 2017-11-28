void
Adaptation::Ecap::HeaderRep::add(const Name &name, const Value &value)
{
    const Http::HdrType squidId = TranslateHeaderId(name); // Http::HdrType::OTHER OK
    HttpHeaderEntry *e = new HttpHeaderEntry(squidId, name.image().c_str(),
            value.toString().c_str());
    theHeader.addEntry(e);

    if (squidId == Http::HdrType::CONTENT_LENGTH)
        theMessage.content_length = theHeader.getInt64(Http::HdrType::CONTENT_LENGTH);
}