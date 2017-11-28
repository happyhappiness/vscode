bool
ACLCertificateData::match(SSL *ssl)
{
    if (!ssl)
        return 0;

    char const *value = sslAttributeCall(ssl, attribute);

    if (value == NULL)
        return 0;

    return values.match(value);
}