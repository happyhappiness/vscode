const char *
Ssl::getErrorName(Ssl::ssl_error_t value)
{

    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (TheSslDetailMap[i].value == value)
            return TheSslDetailMap[i].name;
    }

    return NULL;
}