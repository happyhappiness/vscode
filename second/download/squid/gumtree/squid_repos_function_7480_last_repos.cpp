void
Security::NegotiationHistory::retrieveParsedInfo(Security::TlsDetails::Pointer const &details)
{
    if (details) {
        helloVersion_ = details->tlsVersion;
        supportedVersion_ = details->tlsSupportedVersion;
    }
}