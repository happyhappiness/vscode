const char *
Ssl::GetErrorDescr(Ssl::ssl_error_t value)
{
    return ErrorDetailsManager::GetInstance().getDefaultErrorDescr(value);
}