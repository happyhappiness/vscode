void
Ssl::ServerBio::setClientFeatures(Security::TlsDetails::Pointer const &details, SBuf const &aHello)
{
    clientTlsDetails = details;
    clientSentHello = aHello;
}