    {X509_V_ERR_AKID_SKID_MISMATCH,
     "X509_V_ERR_AKID_SKID_MISMATCH"},
    {X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH,
     "X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH"},
    {X509_V_ERR_KEYUSAGE_NO_CERTSIGN,
     "X509_V_ERR_KEYUSAGE_NO_CERTSIGN"},
    {X509_V_ERR_APPLICATION_VERIFICATION,
     "X509_V_ERR_APPLICATION_VERIFICATION"},
    { SSL_ERROR_NONE, "SSL_ERROR_NONE"},
    {SSL_ERROR_NONE, NULL}
};

static void loadSslErrorMap()
{
    assert(TheSslErrors.empty());
    for (int i = 0; TheSslErrorArray[i].name; ++i) {
        TheSslErrors[TheSslErrorArray[i].value] = &TheSslErrorArray[i];
    }
}

Ssl::ssl_error_t Ssl::GetErrorCode(const char *name)
{
    //TODO: use a std::map?
    for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
        if (strcmp(name, TheSslErrorArray[i].name) == 0)
            return TheSslErrorArray[i].value;
    }
    return SSL_ERROR_NONE;
}

Ssl::ssl_error_t
Ssl::ParseErrorString(const char *name)
{
    assert(name);

    const Ssl::ssl_error_t ssl_error = GetErrorCode(name);
    if (ssl_error != SSL_ERROR_NONE)
        return ssl_error;

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
            return value;
        fatalf("Too small or too bug SSL error code '%s'", name);
    }

    fatalf("Unknown SSL error name '%s'", name);
    return SSL_ERROR_SSL; // not reached
}

const char *Ssl::GetErrorName(Ssl::ssl_error_t value)
{
    if (TheSslErrors.empty())
        loadSslErrorMap();
