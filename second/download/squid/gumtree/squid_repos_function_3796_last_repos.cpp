BIO *
Ssl::Bio::Create(const int fd, Security::Io::Type type)
{
#if HAVE_LIBCRYPTO_BIO_METH_NEW
    if (!SquidMethods) {
        SquidMethods = BIO_meth_new(BIO_TYPE_SOCKET, "squid");
        BIO_meth_set_write(SquidMethods, squid_bio_write);
        BIO_meth_set_read(SquidMethods, squid_bio_read);
        BIO_meth_set_puts(SquidMethods, squid_bio_puts);
        BIO_meth_set_gets(SquidMethods, NULL);
        BIO_meth_set_ctrl(SquidMethods, squid_bio_ctrl);
        BIO_meth_set_create(SquidMethods, squid_bio_create);
        BIO_meth_set_destroy(SquidMethods, squid_bio_destroy);
    }
    const BIO_METHOD *useMethod = SquidMethods;
#else
    BIO_METHOD *useMethod = &SquidMethods;
#endif

    if (BIO *bio = BIO_new(useMethod)) {
        BIO_int_ctrl(bio, BIO_C_SET_FD, type, fd);
        return bio;
    }
    return NULL;
}