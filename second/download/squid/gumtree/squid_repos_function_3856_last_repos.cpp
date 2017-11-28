const char *
hasAuthorityInfoAccessCaIssuers(X509 *cert)
{
    AUTHORITY_INFO_ACCESS *info;
    if (!cert)
        return nullptr;
    info = static_cast<AUTHORITY_INFO_ACCESS *>(X509_get_ext_d2i(cert, NID_info_access, NULL, NULL));
    if (!info)
        return nullptr;

    static char uri[MAX_URL];
    uri[0] = '\0';

    for (int i = 0; i < sk_ACCESS_DESCRIPTION_num(info); i++) {
        ACCESS_DESCRIPTION *ad = sk_ACCESS_DESCRIPTION_value(info, i);
        if (OBJ_obj2nid(ad->method) == NID_ad_ca_issuers) {
            if (ad->location->type == GEN_URI) {
                xstrncpy(uri,
                         reinterpret_cast<const char *>(
#if HAVE_LIBCRYPTO_ASN1_STRING_GET0_DATA
                             ASN1_STRING_get0_data(ad->location->d.uniformResourceIdentifier)
#else
                             ASN1_STRING_data(ad->location->d.uniformResourceIdentifier)
#endif
                         ),
                         sizeof(uri));
            }
            break;
        }
    }
    AUTHORITY_INFO_ACCESS_free(info);
    return uri[0] != '\0' ? uri : nullptr;
}