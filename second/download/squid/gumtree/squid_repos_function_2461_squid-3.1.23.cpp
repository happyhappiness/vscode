static int check_domain( void *check_data, ASN1_STRING *cn_data)
{
    char cn[1024];
    const char *server = (const char *)check_data;

    if (cn_data->length > (int)sizeof(cn) - 1) {
        return 1; //if does not fit our buffer just ignore
    }
    memcpy(cn, cn_data->data, cn_data->length);
    cn[cn_data->length] = '\0';
    debugs(83, 4, "Verifying server domain " << server << " to certificate name/subjectAltName " << cn);
    return matchDomainName(server, cn[0] == '*' ? cn + 1 : cn);
}