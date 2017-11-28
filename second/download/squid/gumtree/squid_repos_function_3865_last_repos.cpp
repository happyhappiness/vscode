bool
Ssl::loadSquidUntrusted(const char *path)
{
    return Ssl::loadCerts(path, SquidUntrustedCerts);
}