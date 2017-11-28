void
HttpHeader::compact()
{
    // TODO: optimize removal, or possibly make it so that's not needed.
    std::vector<HttpHeaderEntry *>::iterator newend;
    newend = std::remove(entries.begin(), entries.end(), static_cast<HttpHeaderEntry *>(NULL));
    entries.resize(newend-entries.begin());
}