void Adaptation::Icap::History::setIcapLastHeader(const HttpHeader * lih)
{
    lastIcapHeader.clean();
    lastIcapHeader.update(lih, NULL);
}