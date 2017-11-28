const char *sslGetUserAttribute(SSL *ssl, const char *attribute_name)
{
    if (!ssl)
        return NULL;

    X509 *cert = SSL_get_peer_certificate(ssl);

    const char *attr = Ssl::GetX509UserAttribute(cert, attribute_name);

    X509_free(cert);
    return attr;
}