Security::ErrorCode Ssl::GetErrorCode(const char *name)
{
    //TODO: use a std::map?
    for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
        if (strcmp(name, TheSslErrorArray[i].name) == 0)
            return TheSslErrorArray[i].value;
    }
    return SSL_ERROR_NONE;
}