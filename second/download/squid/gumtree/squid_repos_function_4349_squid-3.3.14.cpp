const char *Ssl::ErrorDetail::notafter() const
{
    if (!broken_cert)
        return "[Not available]";

    static char tmpBuffer[256]; // A temporary buffer
    ASN1_UTCTIME * tm = X509_get_notAfter(broken_cert.get());
    Ssl::asn1timeToString(tm, tmpBuffer, sizeof(tmpBuffer));
    return tmpBuffer;
}