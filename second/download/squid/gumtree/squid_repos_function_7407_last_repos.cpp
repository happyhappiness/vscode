void
Security::PeerConnector::certDownloadingDone(SBuf &obj, int downloadStatus)
{
    ++certsDownloads;
    debugs(81, 5, "Certificate downloading status: " << downloadStatus << " certificate size: " << obj.length());

    // get ServerBio from SSL object
    const int fd = serverConnection()->fd;
    Security::SessionPointer session(fd_table[fd].ssl);
    BIO *b = SSL_get_rbio(session.get());
    Ssl::ServerBio *srvBio = static_cast<Ssl::ServerBio *>(BIO_get_data(b));

    // Parse Certificate. Assume that it is in DER format.
    // According to RFC 4325:
    //  The server must provide a DER encoded certificate or a collection
    // collection of certificates in a "certs-only" CMS message.
    //  The applications MUST accept DER encoded certificates and SHOULD
    // be able to accept collection of certificates.
    // TODO: support collection of certificates
    const unsigned char *raw = (const unsigned char*)obj.rawContent();
    if (X509 *cert = d2i_X509(NULL, &raw, obj.length())) {
        char buffer[1024];
        debugs(81, 5, "Retrieved certificate: " << X509_NAME_oneline(X509_get_subject_name(cert), buffer, 1024));
        const Security::CertList &certsList = srvBio->serverCertificatesIfAny();
        if (const char *issuerUri = Ssl::uriOfIssuerIfMissing(cert,  certsList)) {
            urlsOfMissingCerts.push(SBuf(issuerUri));
        }
        Ssl::SSL_add_untrusted_cert(session.get(), cert);
    }

    // Check if there are URIs to download from and if yes start downloading
    // the first in queue.
    if (urlsOfMissingCerts.size() && certsDownloads <= MaxCertsDownloads) {
        startCertDownloading(urlsOfMissingCerts.front());
        urlsOfMissingCerts.pop();
        return;
    }

    srvBio->holdRead(false);
    Security::PeerConnector::NegotiateSsl(serverConnection()->fd, this);
}