BIO *
Ssl::Bio::Create(const int fd, Ssl::Bio::Type type)
{
    if (BIO *bio = BIO_new(&SquidMethods)) {
        BIO_int_ctrl(bio, BIO_C_SET_FD, type, fd);
        return bio;
    }
    return NULL;
}