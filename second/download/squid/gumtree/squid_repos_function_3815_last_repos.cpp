static int
squid_bio_create(BIO *bi)
{
#if !HAVE_LIBCRYPTO_BIO_GET_INIT
    bi->init = 0; // set when we store Bio object and socket fd (BIO_C_SET_FD)
    bi->num = 0;
    bi->flags = 0;
#else
    // No need to set more, openSSL initialize BIO memory to zero.
#endif

    BIO_set_data(bi, NULL);
    return 1;
}