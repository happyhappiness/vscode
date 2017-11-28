Ssl::CertValidationHelper * Ssl::CertValidationHelper::GetInstance()
{
    static Ssl::CertValidationHelper sslHelper;
    if (!Ssl::TheConfig.ssl_crt_validator)
        return NULL;
    return &sslHelper;
}