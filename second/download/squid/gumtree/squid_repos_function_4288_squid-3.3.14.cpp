const char *
sslGetUserAttribute(SSL * ssl, const char *attribute_name)
{
    X509 *cert;
    X509_NAME *name;
    const char *ret;

    if (!ssl)
        return NULL;

    cert = SSL_get_peer_certificate(ssl);

    if (!cert)
        return NULL;

    name = X509_get_subject_name(cert);

    ret = ssl_get_attribute(name, attribute_name);

    X509_free(cert);

    return ret;
}