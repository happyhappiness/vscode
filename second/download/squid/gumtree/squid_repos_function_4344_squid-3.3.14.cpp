const char  *Ssl::ErrorDetail::subject() const
{
    if (!broken_cert)
        return "[Not available]";

    static char tmpBuffer[256]; // A temporary buffer
    X509_NAME_oneline(X509_get_subject_name(broken_cert.get()), tmpBuffer,
                      sizeof(tmpBuffer));
    return tmpBuffer;
}