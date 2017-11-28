Ssl::ssl_error_t
Ssl::parseErrorString(const char *name)
{
    assert(name);

    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (strcmp(name, TheSslDetailMap[i].name) == 0)
            return TheSslDetailMap[i].value;
    }

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
            return value;
        fatalf("Too small or too bug SSL error code '%s'", name);
    }

    fatalf("Unknown SSL error name '%s'", name);
    return SSL_ERROR_SSL; // not reached
}