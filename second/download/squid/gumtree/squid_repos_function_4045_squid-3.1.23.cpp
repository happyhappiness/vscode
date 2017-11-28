void Adaptation::Icap::History::mergeIcapHeaders(const HttpHeader * lih)
{
    mergeOfIcapHeaders.update(lih, NULL);
    mergeOfIcapHeaders.compact();
}