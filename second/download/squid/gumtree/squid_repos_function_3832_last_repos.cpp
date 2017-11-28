bool Ssl::checkX509ServerValidity(X509 *cert, const char *server)
{
    return matchX509CommonNames(cert, (void *)server, check_domain);
}