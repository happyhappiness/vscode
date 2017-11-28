void
Ssl::ServerBio::stateChanged(const SSL *ssl, int where, int ret)
{
    Ssl::Bio::stateChanged(ssl, where, ret);
}