Ssl::Errors *
Ssl::ParseErrorString(const char *name)
{
    assert(name);

    const Ssl::ssl_error_t ssl_error = GetErrorCode(name);
    if (ssl_error != SSL_ERROR_NONE)
        return new Ssl::Errors(ssl_error);

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
            return new Ssl::Errors(value);
        fatalf("Too small or too bug SSL error code '%s'", name);
    }

    if (TheSslErrorShortcuts.empty())
        loadSslErrorShortcutsMap();

    const SslErrorShortcuts::const_iterator it = TheSslErrorShortcuts.find(name);
    if (it != TheSslErrorShortcuts.end()) {
        // Should not be empty...
        assert(it->second[0] != SSL_ERROR_NONE);
        Ssl::Errors *errors = new Ssl::Errors(it->second[0]);
        for (int i =1; it->second[i] != SSL_ERROR_NONE; ++i) {
            errors->push_back_unique(it->second[i]);
        }
        return errors;
    }

    fatalf("Unknown SSL error name '%s'", name);
    return NULL; // not reached
}