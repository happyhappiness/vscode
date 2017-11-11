EVP_PKEY *SSL_read_PrivateKey(char* filename, EVP_PKEY **key, modssl_read_bio_cb_fn *cb, void *s)
{
    EVP_PKEY *rc;
    BIO *bioS;
    BIO *bioF;

    /* 1. try PEM (= DER+Base64+headers) */
    if ((bioS=BIO_new_file(filename, "r")) == NULL)
        return NULL;
    rc = modssl_PEM_read_bio_PrivateKey(bioS, key, cb, s);
    BIO_free(bioS);

    if (rc == NULL) {
        /* 2. try DER+Base64 */
        if ((bioS = BIO_new_file(filename, "r")) == NULL)
            return NULL;

        if ((bioF = BIO_new(BIO_f_base64())) == NULL) {
            BIO_free(bioS);
            return NULL;
        }
        bioS = BIO_push(bioF, bioS);
        rc = d2i_PrivateKey_bio(bioS, NULL);
        BIO_free_all(bioS);

        if (rc == NULL) {
            /* 3. try plain DER */
            if ((bioS = BIO_new_file(filename, "r")) == NULL)
                return NULL;
            rc = d2i_PrivateKey_bio(bioS, NULL);
            BIO_free(bioS);
        }
    }
    if (rc != NULL && key != NULL) {
        if (*key != NULL)
            EVP_PKEY_free(*key);
        *key = rc;
    }
    return rc;
}