bool
ACLCertificateData::match(X509 *cert)
{
    if (!cert)
        return 0;

    char const *value = sslAttributeCall(cert, attribute);
    debugs(28, 6, (attribute ? attribute : "value") << "=" << value);
    if (value == NULL)
        return 0;

    return values.match(value);
}