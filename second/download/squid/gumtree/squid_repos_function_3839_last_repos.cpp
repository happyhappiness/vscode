const char *
Ssl::GetX509UserAttribute(X509 * cert, const char *attribute_name)
{
    X509_NAME *name;
    const char *ret;

    if (!cert)
        return NULL;

    name = X509_get_subject_name(cert);

    ret = ssl_get_attribute(name, attribute_name);

    return ret;
}