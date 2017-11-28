void
Ssl::missingChainCertificatesUrls(std::queue<SBuf> &URIs, Security::CertList const &serverCertificates)
{
    if (!serverCertificates.size())
        return;

    for (const auto &i : serverCertificates) {
        if (const char *issuerUri = uriOfIssuerIfMissing(i.get(), serverCertificates))
            URIs.push(SBuf(issuerUri));
    }
}