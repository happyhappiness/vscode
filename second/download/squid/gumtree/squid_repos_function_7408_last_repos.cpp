bool
Security::PeerConnector::checkForMissingCertificates()
{
    // Check for nested SSL certificates downloads. For example when the
    // certificate located in an SSL site which requires to download a
    // a missing certificate (... from an SSL site which requires to ...).

    const Downloader *csd = (request ? request->downloader.get() : nullptr);
    if (csd && csd->nestedLevel() >= MaxNestedDownloads)
        return false;

    const int fd = serverConnection()->fd;
    Security::SessionPointer session(fd_table[fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));
    const Security::CertList &certs = srvBio->serverCertificatesIfAny();

    if (certs.size()) {
        debugs(83, 5, "SSL server sent " << certs.size() << " certificates");
        Ssl::missingChainCertificatesUrls(urlsOfMissingCerts, certs);
        if (urlsOfMissingCerts.size()) {
            startCertDownloading(urlsOfMissingCerts.front());
            urlsOfMissingCerts.pop();
            return true;
        }
    }

    return false;
}