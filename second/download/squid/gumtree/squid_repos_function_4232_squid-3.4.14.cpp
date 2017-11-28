void Adaptation::Icap::Options::cfgTransferList(const HttpHeader *h, TransferList &list)
{
    const String buf = h->getByName(list.name);
    bool foundStar = false;
    list.parse(buf, foundStar);

    if (foundStar) {
        theTransfers.byDefault = &list;
        debugs(93,5, HERE << "set default transfer to " << list.name);
    }

    list.report(5, "Adaptation::Icap::Options::cfgTransferList: ");
}