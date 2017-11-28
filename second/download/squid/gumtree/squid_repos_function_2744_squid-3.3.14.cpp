void
HttpHeader::compact()
{
    entries.prune(NULL);
}