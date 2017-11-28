Adaptation::Ecap::RequestLineRep::Area
Adaptation::Ecap::RequestLineRep::uri() const
{
    const char *fullUrl = urlCanonical(&theMessage);
    Must(fullUrl);
    // optimize: avoid copying by having an Area::Detail that locks theMessage
    return Area::FromTempBuffer(fullUrl, strlen(fullUrl));
}