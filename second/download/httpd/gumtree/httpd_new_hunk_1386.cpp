                                 int idx)
{
    SSLModConfigRec *mc = myModConfig(s);
    ssl_asn1_t *asn1;
    MODSSL_D2I_PrivateKey_CONST unsigned char *ptr;
    const char *type = ssl_asn1_keystr(idx);
    int pkey_type;
    EVP_PKEY *pkey;

#ifndef OPENSSL_NO_EC
    if (idx == SSL_AIDX_ECC)
      pkey_type = EVP_PKEY_EC;
    else
#endif
    pkey_type = (idx == SSL_AIDX_RSA) ? EVP_PKEY_RSA : EVP_PKEY_DSA;

    if (!(asn1 = ssl_asn1_table_get(mc->tPrivateKey, id))) {
        return FALSE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Configuring %s server private key", type);
