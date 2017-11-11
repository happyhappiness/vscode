const char *ssl_asn1_keystr(int keytype)
{
    if (keytype >= SSL_AIDX_MAX) {
        return NULL;
    }

    return ssl_asn1_key_types[keytype];
}