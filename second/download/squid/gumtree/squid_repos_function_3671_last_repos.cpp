bool Adaptation::Icap::ServiceRep::wantsPreview(const SBuf &urlPath, size_t &wantedSize) const
{
    Must(hasOptions());

    if (theOptions->preview < 0)
        return false;

    if (theOptions->transferKind(urlPath) != Adaptation::Icap::Options::xferPreview)
        return false;

    wantedSize = theOptions->preview;

    return true;
}