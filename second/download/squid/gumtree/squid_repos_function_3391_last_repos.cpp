Adaptation::Ecap::RequestLineRep::Area
Adaptation::Ecap::RequestLineRep::uri() const
{
    const SBuf &fullUrl = theMessage.effectiveRequestUri();
    // XXX: effectiveRequestUri() cannot return NULL or even empty string, some other problem?
    Must(!fullUrl.isEmpty());
    // optimize: avoid copying by having an Area::Detail that locks theMessage
    return Area::FromTempBuffer(fullUrl.rawContent(), fullUrl.length());
}