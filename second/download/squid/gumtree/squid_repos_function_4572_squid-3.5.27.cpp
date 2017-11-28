const char *Ssl::GetErrorName(Ssl::ssl_error_t value)
{
    if (TheSslErrors.empty())
        loadSslErrorMap();

    const SslErrors::const_iterator it = TheSslErrors.find(value);
    if (it != TheSslErrors.end())
        return it->second->name;

    return NULL;
}