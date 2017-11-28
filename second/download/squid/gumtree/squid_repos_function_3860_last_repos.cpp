const char *
Ssl::uriOfIssuerIfMissing(X509 *cert, Security::CertList const &serverCertificates)
{
    if (!cert || !serverCertificates.size())
        return nullptr;

    if (!findCertIssuer(serverCertificates, cert)) {
        //if issuer is missing
        if (!findCertIssuerFast(SquidUntrustedCerts, cert)) {
            // and issuer not found in local untrusted certificates database
            if (const char *issuerUri = hasAuthorityInfoAccessCaIssuers(cert)) {
                // There is a URI where we can download a certificate.
                return issuerUri;
            }
        }
    }
    return nullptr;
}