DH *ssl_dh_GetParamFromFile(char *file)
{
    DH *dh = NULL;
    BIO *bio;

    if ((bio = BIO_new_file(file, "r")) == NULL)
        return NULL;
#if SSL_LIBRARY_VERSION < 0x00904000
    dh = PEM_read_bio_DHparams(bio, NULL, NULL);
#else
    dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
#endif
    BIO_free(bio);
    return (dh);
}