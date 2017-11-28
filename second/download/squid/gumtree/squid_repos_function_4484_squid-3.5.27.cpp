SSL *
Ssl::CreateServer(SSL_CTX *sslContext, const int fd, const char *squidCtx)
{
    return SslCreate(sslContext, fd, Ssl::Bio::BIO_TO_CLIENT, squidCtx);
}