void
HttpHeader::compact()
{
    // TODO: optimize removal, or possibly make it so that's not needed.
    entries.erase( std::remove(entries.begin(), entries.end(), nullptr),
                   entries.end());
}