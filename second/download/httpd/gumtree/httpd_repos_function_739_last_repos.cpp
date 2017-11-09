static int bio_filter_create(BIO *bio)
{
    BIO_set_shutdown(bio, 1);
    BIO_set_init(bio, 1);
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    /* No setter method for OpenSSL 1.1.0 available,
     * but I can't find any functional use of the
     * "num" field there either.
     */
    bio->num = -1;
#endif
    BIO_set_data(bio, NULL);

    return 1;
}