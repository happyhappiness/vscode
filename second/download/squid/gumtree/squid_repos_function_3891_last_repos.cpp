const Security::CertErrors *
Ssl::ServerBump::sslErrors() const
{
    if (!serverSession)
        return NULL;

    const Security::CertErrors *errs = static_cast<const Security::CertErrors*>(SSL_get_ex_data(serverSession.get(), ssl_ex_index_ssl_errors));
    return errs;
}