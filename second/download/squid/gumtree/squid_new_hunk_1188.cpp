{
    assert(TheSslErrorShortcuts.empty());
    for (int i = 0; TheSslErrorShortcutsArray[i].name; ++i)
        TheSslErrorShortcuts[TheSslErrorShortcutsArray[i].name] = TheSslErrorShortcutsArray[i].errors;
}

Security::ErrorCode Ssl::GetErrorCode(const char *name)
{
    //TODO: use a std::map?
    for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
        if (strcmp(name, TheSslErrorArray[i].name) == 0)
            return TheSslErrorArray[i].value;
    }
    return SSL_ERROR_NONE;
}

bool
Ssl::ParseErrorString(const char *name, Security::Errors &errors)
{
    assert(name);

    const Security::ErrorCode ssl_error = GetErrorCode(name);
    if (ssl_error != SSL_ERROR_NONE) {
        errors.emplace(ssl_error);
        return true;
    }

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX) {
            errors.emplace(value);
            return true;
        }
        fatalf("Too small or too big TLS error code '%s'", name);
    }

    if (TheSslErrorShortcuts.empty())
        loadSslErrorShortcutsMap();

    const SslErrorShortcuts::const_iterator it = TheSslErrorShortcuts.find(name);
    if (it != TheSslErrorShortcuts.end()) {
        // Should not be empty...
        assert(it->second[0] != SSL_ERROR_NONE);
        for (int i = 0; it->second[i] != SSL_ERROR_NONE; ++i) {
            errors.emplace(it->second[i]);
        }
        return true;
    }

    fatalf("Unknown TLS error name '%s'", name);
    return false; // not reached
}

const char *Ssl::GetErrorName(Security::ErrorCode value)
{
    if (TheSslErrors.empty())
        loadSslErrorMap();

    const SslErrors::const_iterator it = TheSslErrors.find(value);
    if (it != TheSslErrors.end())
