const char *Ssl::ErrorDetail::notafter() const
{
    if (!peer_cert)
        return "[Not available]";

    static char tmpBuffer[256]; // A temporary buffer
    ASN1_UTCTIME * tm = X509_get_notAfter(peer_cert.get());
    Ssl::asn1timeToString(tm, tmpBuffer, sizeof(tmpBuffer));
    return tmpBuffer;
}