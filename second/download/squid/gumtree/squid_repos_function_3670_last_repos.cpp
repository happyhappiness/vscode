bool Adaptation::Icap::ServiceRep::wantsUrl(const SBuf &urlPath) const
{
    Must(hasOptions());
    return theOptions->transferKind(urlPath) != Adaptation::Icap::Options::xferIgnore;
}