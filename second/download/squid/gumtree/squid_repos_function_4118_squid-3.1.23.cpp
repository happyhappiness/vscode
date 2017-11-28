const char *Ssl::ErrorDetail::ca_name() const
{
    if (!peer_cert)
        return "[Not available]";

    static char tmpBuffer[256]; // A temporary buffer
    X509_NAME_oneline(X509_get_issuer_name(peer_cert.get()), tmpBuffer, sizeof(tmpBuffer));
    return tmpBuffer;
}