const char *
Ssl::GetX509CAAttribute(X509 * cert, const char *attribute_name)
{

    X509_NAME *name;
    const char *ret;

    if (!cert)
        return NULL;

    name = X509_get_issuer_name(cert);

    ret = ssl_get_attribute(name, attribute_name);

    return ret;
}