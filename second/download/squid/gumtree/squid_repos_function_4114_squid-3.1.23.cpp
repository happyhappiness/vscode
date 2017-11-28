static const char *getErrorDetail(Ssl::ssl_error_t value)
{
    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (TheSslDetailMap[i].value == value)
            return TheSslDetailMap[i].detail;
    }

    // we must always return something because ErrorDetail::buildDetail
    // will hit an assertion
    return SslErrorDetailDefaultStr;
}