Adaptation::Icap::Options::TransferKind
Adaptation::Icap::Options::transferKind(const SBuf &urlPath) const
{
    if (theTransfers.preview.matches(urlPath))
        return xferPreview;

    if (theTransfers.complete.matches(urlPath))
        return xferComplete;

    if (theTransfers.ignore.matches(urlPath))
        return xferIgnore;

    debugs(93,7, "url " << urlPath << " matches no extensions; " <<
           "using default: " << theTransfers.byDefault->name);
    return theTransfers.byDefault->kind;
}