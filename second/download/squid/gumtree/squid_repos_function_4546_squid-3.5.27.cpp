void
Ssl::ServerBump::attachServerSSL(SSL *ssl)
{
    if (serverSSL.get())
        return;

    serverSSL.resetAndLock(ssl);
}