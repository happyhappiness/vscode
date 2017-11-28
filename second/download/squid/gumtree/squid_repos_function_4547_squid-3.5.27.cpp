const Ssl::CertErrors *
Ssl::ServerBump::sslErrors() const
{
    if (!serverSSL.get())
        return NULL;

    const Ssl::CertErrors *errs = static_cast<const Ssl::CertErrors*>(SSL_get_ex_data(serverSSL.get(), ssl_ex_index_ssl_errors));
    return errs;
}