static bool
addAltNameWithSubjectCn(Security::CertPointer &cert)
{
    X509_NAME *name = X509_get_subject_name(cert.get());
    if (!name)
        return false;

    const int loc = X509_NAME_get_index_by_NID(name, NID_commonName, -1);
    if (loc < 0)
        return false;

    ASN1_STRING *cn_data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, loc));
    if (!cn_data)
        return false;

    char dnsName[1024]; // DNS names are limited to 256 characters
    const int res = snprintf(dnsName, sizeof(dnsName), "DNS:%*s", cn_data->length, cn_data->data);
    if (res <= 0 || res >= static_cast<int>(sizeof(dnsName)))
        return false;

    X509_EXTENSION *ext = X509V3_EXT_conf_nid(NULL, NULL, NID_subject_alt_name, dnsName);
    if (!ext)
        return false;

    const bool result = X509_add_ext(cert.get(), ext, -1);

    X509_EXTENSION_free(ext);
    return result;
}