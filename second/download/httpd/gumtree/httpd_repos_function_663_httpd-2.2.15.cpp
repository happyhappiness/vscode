static EVP_PKEY *d2i_PrivateKey_bio(BIO *bio, EVP_PKEY **key)
{
     return ((EVP_PKEY *)ASN1_d2i_bio(
             (char *(*)())EVP_PKEY_new,
             (char *(*)())d2i_PrivateKey,
             (bio), (unsigned char **)(key)));
}