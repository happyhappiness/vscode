const char *Ssl::ErrorDetail::notafter() const
{
    if (broken_cert.get()) {
        if (ASN1_UTCTIME * tm = X509_get_notAfter(broken_cert.get())) {
            static char tmpBuffer[256]; // A temporary buffer
            Ssl::asn1timeToString(tm, tmpBuffer, sizeof(tmpBuffer));
            return tmpBuffer;
        }
    }
    return "[Not available]";
}