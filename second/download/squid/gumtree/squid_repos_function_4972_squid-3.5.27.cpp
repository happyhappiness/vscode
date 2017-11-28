template<class MatchType>
int
check_cert_domain( void *check_data, ASN1_STRING *cn_data)
{
    char cn[1024];
    ACLData<MatchType> * data = (ACLData<MatchType> *)check_data;

    if (cn_data->length > (int)sizeof(cn) - 1)
        return 1; // ignore data that does not fit our buffer

    char *s = reinterpret_cast<char *>(cn_data->data);
    char *d = cn;
    for (int i = 0; i < cn_data->length; ++i, ++d, ++s) {
        if (*s == '\0')
            return 1; // always a domain mismatch. contains 0x00
        *d = *s;
    }
    cn[cn_data->length] = '\0';
    debugs(28, 4, "Verifying certificate name/subjectAltName " << cn);
    if (data->match(cn))
        return 0;
    return 1;
}